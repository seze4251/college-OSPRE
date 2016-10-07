function [validSolution, minAccuracy ] = PositionVelocityError( pixels, FOV, ...
    plots, pixPerDeg, plotStr, error_vec )
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
% error_vec - A vector of the pixel errors that is allowed for image
% proccessing
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
[ sigma_x, sigma_y, sigma_eff ] = pixel2DegError( px_deg_x, px_deg_y, error_vec);

% Determine Position Error (CAMERON FUNCTION HERE)
% Outputs required

alpha = 10;                      % Sample error in alpha, deg
beta = 10;                       % Sample error in beta, deg

[Rerror_rangeEarth, range] = Earth_Range_Position_Error(alpha, beta, sigma_eff);
Rerror_rangeMoon = Moon_Range_Position_Error(alpha, beta, sigma_eff);
Rerror_Angles = Angles_Position_Error(alpha, beta, sigma_eff);


% Determine Minimum Position Error  (ANTHONY FUNCTION 1 HERE)
% Outputs required
[r_error, MethodMin] = calcRminErr(Rerror_rangeEarth, Rerror_rangeMoon, Rerror_Angles);

% Determine Velocity Error
v_error = velocityError( r_error.* 1e3 );

% Determine minimum Degree accuracy needed to meet requirments
targetPosErr = 1000; %km
targetVelErr = 250; %m/s
[minAccuracyIndex, validSolution] = calcMaxDegErr(r_error, v_error, targetPosErr, targetVelErr);


% Switch valid solution to match function requirments
if validSolution == 0
    validSolution = -1;
    minAccuracy = 0;
else
    minAccuracy = sigma_eff(minAccuracyIndex);
    validSolution = 0;
end

% Plot Results
if plots == 1 || plots == 3
    % Position Graph
    figure;
    hold on;
    a = 1;
    
    for i = 1 : size(r_error,1)
        plot(range, r_error(i,:));
        str_pos{a} = sprintf('Pixel Error %2.2f (Pixel)', error_vec(i));
        a = a + 1;
    end
    hline(1000,'k--','');
    legend(str_pos);
    xlabel('Range from Earth (km)');
    ylabel('Position Error (km)');
    title(plotStr{1})
    hold off;
    
    % Velocity Graph
    figure;
    hold on;
    a = 1;
    for i = 1 : size(v_error,1)
        plot(range(1:end-1), v_error(i,:));
        str_vel{a} = sprintf('Pixel Error %2.2f (Pixel)', error_vec(i));
        a = a + 1;
    end
    
    legend(str_vel);
    hline(250,'k--','');
    xlabel('Range from Earth (km)');
    ylabel('Velocity Error (m/s)');
    title(plotStr{2})
    hold off;
    
    figure;
    % Choose a random Deg and plot it
    hold on
    row = minAccuracyIndex;
    plot(range, Rerror_rangeEarth(row,:),'b')
    plot(range, Rerror_rangeMoon(row,:),'r')
    plot(range, Rerror_Angles(row,:),'g')
    plot(range,1000*ones(length(range)),'k--')
    legend('Earth Ranging', 'Moon Ranging', 'Angles');
    xlabel('Range from Earth (km)');
    ylabel('Position Error (km)');
    str_tit = sprintf('Position Error vs Range \n  with a Maximum Allowable Degree Error of %1.3f deg',sigma_eff(row));
    title(str_tit)
    ylim([0 1400])
end

% if plots == 2 || plots == 3
%     figure;
%     row_vec = [ 5  50];
%     a = 1;
%     for i = row_vec
%         subplot(1,2,a);
%         a = a + 1;
%         hold on;
%         for j = 1 : length(r_error(1,:))
%             if(MethodMin(i,j) == 1)
%                 plot(range(j),r_error(i,j),'b*')
%             elseif(MethodMin(i,j) == 2)
%                 plot(range(j),r_error(i,j),'r*')
%             else
%                 plot(range(j),r_error(i,j),'g*')
%             end
%         end
%         legend('Ranging to Earth', 'Ranging to Moon', 'Angles');
%         xlabel('Range (km)');
%         ylabel('Position Error (km)');
%         str_tit = sprintf('Method vs Position Error for \n image processing accuracy of %1.3f deg',sigma_eff(i));
%         title(str_tit)
%     end
% end

end


