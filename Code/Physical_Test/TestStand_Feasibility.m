% Seth Zegelstein
% 9/9/2016
% ASEN 4018
% Purpose - Conduct Various Feasibility Studies and produce different
% graphs
clear all; close all; clc;

R_Earth = 6378.137e3;  %m
Distance_Earth_Moon = 384400e3; %m

sc_Position = linspace(R_Earth + 500e3, Distance_Earth_Moon, 10000); %km

R_L = linspace(0.1,.3,5); %m

figure;
hold on
for i = 1: length(R_L)
    X(:,i) = R_L(i) * sc_Position ./ R_Earth;
    plot(sc_Position/1000, X(:,i));
    str{i} = ['Light Source Radius of ' num2str(R_L(i)*100) ' (cm)'];
end
legend(str, 'Location', 'Best');
xlabel 'SpaceCraft Position (km)'
ylabel 'Distance Away From Light(m)'
tit = sprintf('Distance from Light Source vs Space Craft Position \n for various Light Sources');
title(tit);



