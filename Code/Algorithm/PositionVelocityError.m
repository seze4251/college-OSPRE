function [validSolution, minAccuracy ] = PositionVelocityError( pixels, FOV, ...
    plots, pixPerDeg, plotStr )
% Cameron Maywood, Anthony Torres, Seth Zegelstein
% Date Created: 9/27/2016
% Date Modified: 10/3/2016
%
% PositionVelocityError
%
% Inputs
% pixels: The number of pixels the image sensor contains 1x1
% FOV: The field of view of the camera (degree) 1x2
% plots: A integer,0 if plots are not desired, 1 if position/veloicty plots
% are desired, 2 if best position method plot is desired 3 if all plots are
% desired 1x1
% pixPerDeg: 0 if we want to use the calculation for pixels per degree 1x1 or,
% a 1 x 2 to skip calculation and use manually computed pixel to degree
% values
% plotStr: If plots == 1, A 1 x 3 cell array with titles for position (plotStr{1}) and
% velocity (plotStr{2}), which position method (plotStr{3}) graphs, else 
% plotStr = 0
%
% Outputs
% minAccuracy: The minimum degree accuracy required from image proccessing
% to satsify both position and velocity requirments
% validSolution: Boolean, 0 if solution can meet error requirments, -1 if
% soultion cannot meet error requirments
%
% Description: Calculates the error in position and velocity, plots the
% results if requested and returns the highest amount of image proccesing
% error allowed to still meet requirments
%
% Assumptions: NONE

% Determine pixels per degree
if pixPerDeg(1) == 0
    [px_deg_x,px_deg_y] = px_deg(pixels, FOV);
else
    px_deg_x = pixPerDeg(1);
    px_deg_y = pixPerDeg(2);
end

% Determine the Degree error from a given pixel per degree
[ sigma_x, sigma_y, sigma_eff, error ] = pixel2DegError( px_deg_x, px_deg_y);

% Determine Position Error (CAMERON FUNCTION HERE)
% Outputs required

alpha = 1;                      % Sample error in alpha, deg
beta = 1;                       % Sample error in beta, deg

Rerror_rangeMoon = Moon_Range_Position_Error(alpha, beta, sigma_eff);
Rerror_Angles = Angles_Position_Error(alpha, beta, sigma_eff);
[Rerror_rangeEarth, range] = Earth_Range_Position_Error(alpha, beta, sigma_eff);


% Determine Minimum Position Error  (ANTHONY FUNCTION 1 HERE)
% Outputs required
[r_error, MethodMin] = calcRminErr(Rerror_rangeEarth, Rerror_rangeMoon, Rerror_Angles);

% Determine Velocity Error
v_error = velocityError( r_error.*1e3 );

% Determine minimum Degree accuracy needed to meet requirments 
targetPosErr = 1000; %km
targetVelErr = 500; %m/s
[minAccuracyIndex, validSolution] = calcMaxDegErr(r_error, v_error, targetPosErr, targetVelErr);

minAccuracy = error(minAccuracyIndex);
%minAccuracy = sigma_eff(minAccuracyIndex);

% Switch valid solution to match function requirments
if validSolution == 0
    validSolution = -1;
else
    validSolution = 0;
end

% Plot Results
if plots == 1 || plots == 3
    % Position Graph
    figure;
    hold on;
    for i = 1 : size(r_error,1)
        plot(range, r_error(i,:));
        str_pos{i} = sprintf('Degree Accuracy %5.5f (deg)', sigma_eff(i));
    end
    legend(str_pos);
    xlabel('Range (km)');
    ylabel('Position Error (km)');
    title(plotStr{1})
    hold off;
    
    % Velocity Graph
    figure;
    hold on;
    for i = 1 : size(v_error,1)
        plot(range(1:end-1), v_error(i,:));
        str_vel{i} = sprintf('Degree Accuracy %5.5f (deg)', sigma_eff(i));
    end

    legend(str_vel);
    xlabel('Range (km)');
    ylabel('Velocity Error (m/s)');
    title(plotStr{2})
    hold off;
end

if plots == 2 || plots == 3
    figure;
    surf(MethodMin)
end

end


