% Seth Zegelstein
% 9/27/2016
% Purpose - FOV Calculation for SR. Projs

%% Field Of View Calculation
%FOV = 2atan(h/2f)
clear all; close all; clc;
samples = 5;
minfocal = 5e-3;
maxfocal = 50e-3;
f = linspace(minfocal, maxfocal, samples);
minSenHeight = 3e-3;
maxSenHeight = 12e-3;
h = linspace(minSenHeight, maxSenHeight, samples);

% i is for h
% j = for j
figure;
hold on;
for i = 1 : samples
    for j = 1 : samples
        FOV(j) = 2*atand(h(i)/(2*f(j)));
    end
    plot(f*1000, FOV);
    str{i} = sprintf('Sensor Height of in %4.2f milimeter ', h(i)*1000);
end
legend(str)
xlabel 'Focal Length (mm)'
ylabel 'Field of View (deg)'
title 'Feild of View vs Focal Length for Various Image Sensor Heights'

