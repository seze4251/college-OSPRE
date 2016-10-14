function [r_error, v_error] = PosVelError2( sigma_eff )
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


alpha = 1;                      % Sample error in alpha, deg
beta = 1;                       % Sample error in beta, deg

[Rerror_rangeEarth, ~] = Earth_Range_Position_Error(alpha, beta, sigma_eff);
Rerror_rangeMoon = Moon_Range_Position_Error(alpha, beta, sigma_eff);
Rerror_Angles = Angles_Position_Error(alpha, beta, sigma_eff);


% Determine Minimum Position Error  (ANTHONY FUNCTION 1 HERE)
% Outputs required
[r_error, ~] = calcRminErr(Rerror_rangeEarth, Rerror_rangeMoon, Rerror_Angles);

% Determine Velocity Error
v_error = velocityError( r_error.* 1e3 );

