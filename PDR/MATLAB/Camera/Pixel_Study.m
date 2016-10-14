% Seth Zegelstein
% 9/11/2016
% Purpose - Determine how many pixels we need to have to determine accurate
% distances to an object distance for various Methods
clear all; close all; clc;

% What can we measure from an image?
% We know the amount of pixels in the camera, the angle of the camera captuers,
% and the

% Fixed quantities
R_Earth = 6378.137; %km
R_Moon = []; %km
d_max = 384400 - 500; %km
d_min = 500; %km

% Variable Quantities
Camera_Angle = pi/180 * linspace(30,150,3); %rad
minPixels = 1;
MaxPixels = 10;

Pixels = linspace(minPixels, MaxPixels, 100); %Pixels

% Assume Camera is square
Pixels_Per_Row = sqrt(Pixels);
Max_Pixels_Per_Row = max(sqrt(Pixels));
Pixels_Measured = 1;

figure;
hold on
for i = 1: length(Camera_Angle)
    alpha(:,i) = (Pixels_Per_Row) * Camera_Angle(i) ./ Max_Pixels_Per_Row;
    distance(:,i) = R_Earth ./ tan(alpha(:,i) / 2);
    plot(Pixels, distance(:,i));
    str{i} = ['Camera Angle ' num2str(180/pi * Camera_Angle(i)) ' (deg)'];
end

legend(str, 'Location', 'Best');
xlabel 'Amount of Pixels (Pixels)'
ylabel 'Distance (km)'
tit = sprintf('Distance vs Space Craft Position');
title(tit);










