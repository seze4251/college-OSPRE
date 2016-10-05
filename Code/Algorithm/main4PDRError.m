% Cameron Maywood, Anthony Torres, Seth Zegelstein
% Date Created: 9/27/2016
% Date Modified:
% Purpose: Main Script for PDR 
close all; clc;

%% Determine Position Velocity Error for best camera that fits in volume requirments
clearvars;

pixels = 8e6; %pixels
FOV = [30 30]; %degrees
plots = 3; % Show Plots
pixPerDeg = 0; % Use pixel and FOV in calculations
plotStr{1} = sprintf('Position Error vs Distance for Camera \n that fits in Volume Constaints');
plotStr{2} = sprintf('Velocity Error vs Distance for Camera \n that fits in Volume Constaints');
pixel_error_vec = linspace(.1,50,100);
[validSolution, minDegAccuracy] = PositionVelocityError( pixels, FOV, plots, pixPerDeg, plotStr, pixel_error_vec );

if validSolution == 0
    str = 'a valid solution.';
else
    str = 'a invalid solution.';
end

fprintf('This option is %s Image processing must be accurate to within %.5f degrees \n in order to meet requirments for top choice \n camera within volume constraints \n', str, minDegAccuracy);

%% Determine Position Velocity Error for best camera that does not fit in volume requirments
clearvars;

pixels = 8e6; %pixels
FOV = [30 30]; %degrees
plots = 3; % Show Plots
pixPerDeg = 0; % Use pixel and FOV in calculations
plotStr{1} = sprintf('Position Error vs Distance for Camera \n outside of Volume Constaints');
plotStr{2} = sprintf('Velocity Error vs Distance for Camera \n oustside of Volume Constaints');
pixel_error_vec = linspace(.1,50,100);
[validSolution, minDegAccuracy] = PositionVelocityError( pixels, FOV, plots, pixPerDeg, plotStr, pixel_error_vec );

if validSolution == 0
    str = 'a valid solution.';
else
    str = 'a invalid solution.';
end

fprintf('\nThis option is %s Image processing must be accurate to within %.5f degrees \n in order to meet requirments for camera outside of \n volume constraints\n ', str, minDegAccuracy);

%% Create pixel/deg plot 
clearvars;

pixels = []; %pixels
FOV = []; %degrees
plots = 0; % Show Plots
plotStr = [];
pixPerDeg = linspace(1,50,10); % Use pixel and FOV in calculations
pixel_error_vec = linspace(.1,50,200);
count = 1;

for i = pixPerDeg
    [validSolution, minDegAccuracy] = PositionVelocityError( pixels, FOV, plots, [i i], plotStr, pixel_error_vec );
    if validSolution == 0
        minDegAccuracy_Plot(count) = minDegAccuracy;
        pixPerDeg_Plot(count) = i;
        count = count + 1;
    end
end

figure;
plot(pixPerDeg, minDegAccuracy_Plot)
xlabel 'Pixel/Degree'
ylabel 'Maximum Allowable Pixel Error From Image Processing (Pixel)'
tit = sprintf('Maximum Image processing Error vs Pixel/Degree \n required for a valid solution');
title(tit);





