clear all; close all ; clc

%% Example for how to run function for our provided WCS and Sony sensor

m = 4192;
n = 3104;
min_ang_dia = 0.88; %deg
resolution = 72; %pix/deg

[CenterPoints,RGB_MATRIX1,RGB_MATRIX2] = Circle_2D(m,n,min_ang_dia,resolution, ...
    'OSPRE/Sample Images/GenImages/im1.jpg', 'OSPRE/Sample Images/GenImages/im2.jpg', 'OSPRE/Sample Images/GenImages/centerPoints.mat');