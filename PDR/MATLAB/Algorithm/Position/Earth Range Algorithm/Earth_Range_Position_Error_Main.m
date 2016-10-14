%% Earth Range Position Error Main
% Author:   Cameron Maywood
% Created:  10/3/2016
% Modified: 10/3/2016

clear all; close all;
%%
alpha = 1;                      % Sample error in alpha, deg
beta = 1;                       % Sample error in beta, deg
sigma_mean = 0.01:0.01:0.1;     % Sample sigma_mean, deg

error_range = Earth_Range_Position_Error(alpha, beta, sigma_mean);