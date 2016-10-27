% Seth Zegelstein
% 10/25/2016
% Purpose - Provide Plots for Dylans Trade Study
%

% Pix Per Degree Values
%FLIR = 25.6 pixels/degree
%Sony = 72.3 pixels/degree
%ZenFone = 177.1 pixels/degree
clc; close all; clearvars;

pixPerDeg = [ 25.6 72.3 177.1]; 
error_vec = linspace(0.1,1,1000);


figure;
hold on
for i = 1 : length(pixPerDeg)
    [maxPosError] = Pos_Vel4( pixPerDeg(i), error_vec );
    plot(error_vec, maxPosError)
end
hline(1000,'k--','Maximum Allowable Position Error')

legend('FLIR Camera 25.6 pix/deg', 'Sony Camera 72.3 pix/deg', 'ZenFone 177.1 pix/deg');
title 'Maximum Position Error in Transfer Orbit vs Pixel Error'
xlabel 'Pixel Error (Pixels)'
ylabel 'Position Error (km)'