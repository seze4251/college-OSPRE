function [ sigma_x, sigma_y, sigma_mean ] = pixel2DegError( px_deg_x, px_deg_y, error_vec)
% Seth Zegelstein, and Anthoney Torres
% Date Created: 10/03/2016
% Date Modified:
%
% pixel2DegError
%
% Inputs:
% px_deg_x: The ratio of (Pixels/Degrees) for the horizontal 
% direction of the camera 1x1
% px_deg_y: The ratio of (Pixels/Degrees) for the vertical
% direction of the camera 1x1
%
% Outputs:
%
% Description:



sigma_x = 1/px_deg_x * error_vec;
sigma_y = 1/px_deg_y * error_vec;
sigma_mean = (sigma_x + sigma_y) /2;

end

