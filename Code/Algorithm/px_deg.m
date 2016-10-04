function [px_deg_x,px_deg_y] = px_deg(MP,FOV)
% Ryan Cutter
% Date Created: 9/20/2016
% Date Modified: 10/3/2016
% Modified By: Seth Zegelstein
% Inputs:
% MP: The number of pixels the image sensor contains 1x1
% FOV: The field of view of the camera (degrees) 1x2
% Outputs:
% px_deg_x: The ratio of (Pixels/Degrees) for the horizontal 
% direction of the camera 1x1
% px_deg_y: The ratio of (Pixels/Degrees) for the vertical
% direction of the camera 1x1
% Description: Creates a pixel per degree ratio for the horizontal and
% vertical directions from camera specs
% Assumptions: Assumes a pixel ratio of a 4:3 (Horizontal, Vertical)

x = FOV(1);
y = FOV(2);

height = sqrt(MP*(3/4));
height = height/100;
height = round(height);
height = height*100;
width = height*(4/3);

px_deg_x = width/x;
px_deg_y = height/y;

end