%% Position Algorithm Error
% Author: Cameron Maywood
% Created: 9/28/2016
% Modified: 9/28/2016

clear all; close all; clc;
%% Ranging Method, Perfect Pointing

%%% Simulation Constants
R_E = 6378.137;                                 % Earth radius, km
comp = 0.5773502692;                            % X,Y,Z components to make unit vector point in diagonal direction
%r_SC_E = [-comp; comp; -comp];                 % sample attitude, unit vector pointing towards earth from upper right quadrant
r_SC_E = [-1; 0; 0];                            % sample attitude, unit vector pointing towards earth from directly in front of it
deg_error = .05;                                % angular diameter error

%% For 302,080 km (minimum angular diameter)
%%% Geometry constants
d1 = 302080.368378;                                             % sample distance, point of minimum angular diameter km
theta_known1 = 2*atand(R_E/d1);                                 % sample angular diameter
theta1 = theta_known1-deg_error:0.001:theta_known1+deg_error;   % possible calculated angular diameters (error introduced)
error_theta1 = theta_known1-theta1;                             % error in calculated theta

%%% Experimental Earth-Spaceceaft distance @ 302,080 km
for i = 1:length(theta1)
	r_E_SC1(i) = norm(-R_E/tand(theta1(i)/2)*r_SC_E);
	error_r1(i) = d1 - r_E_SC1(i);
end

%% For 35,786 km (GEO)
%%% Geometry Constants
d2 = 35786;                                                     % sample distance, point of minimum angular diameter km
theta_known2 = 2*atand(R_E/d2);                                 % sample angular diameter
theta2 = theta_known2-deg_error:0.001:theta_known2+deg_error;   % possible calculated angular diameters (error introduced)
error_theta2 = theta_known2-theta2;                             % error in calculated theta

%%% Experimental Earth-Spaceceaft distance @ 35,786 km
for i = 1:length(theta2)
	r_E_SC2(i) = norm(-R_E/tand(theta2(i)/2)*r_SC_E);
	error_r2(i) = d2 - r_E_SC2(i);
end

%% For 100,000 km
%%% Geometry Constants
d3 = 100000;                                                    % sample distance, point of minimum angular diameter km
theta_known3 = 2*atand(R_E/d3);                                 % sample angular diameter
theta3 = theta_known3-deg_error:0.001:theta_known3+deg_error;   % possible calculated angular diameters (error introduced)
error_theta3 = theta_known3-theta3;                             % error in calculated theta

%%% Experimental Earth-Spaceceaft distance @ 100,000 km
for i = 1:length(theta3)
	r_E_SC3(i) = norm(-R_E/tand(theta3(i)/2)*r_SC_E);
	error_r3(i) = d3 - r_E_SC3(i);
end

%% For 200,000 km
%%% Geometry Constants
d4 = 200000;                                                    % sample distance, point of minimum angular diameter km
theta_known4 = 2*atand(R_E/d4);                                 % sample angular diameter
theta4 = theta_known4-deg_error:0.001:theta_known4+deg_error;   % possible calculated angular diameters (error introduced)
error_theta4 = theta_known4-theta4;                             % error in calculated theta

%%% Experimental Earth-Spaceceaft distance @ 200,000 km
for i = 1:length(theta4)
	r_E_SC4(i) = norm(-R_E/tand(theta4(i)/2)*r_SC_E);
	error_r4(i) = d4 - r_E_SC4(i);
end

%% Plots
plot(error_theta1, error_r1, 'linewidth', 1.5)
hold on
plot(error_theta2, error_r2,  'linewidth', 1.5)
plot(error_theta3, error_r3,  'linewidth', 1.5)
plot(error_theta4, error_r4,  'linewidth', 1.5)
title('Earth Angular Diameter Error vs. Range Error km')
xlabel('\theta error (deg)')
ylabel('Range error (km)')
grid on;
legend('d = 302,080 km (min angular diameter)', 'd = 35,786 km (GEO)', 'd = 100,000 km', 'd = 200,000 km')
axis([-deg_error deg_error -2000 2000])

hline(1000)
hline(-1000)

%% Analytical Error Solution ***NOT WORKING***
% 
% delta_theta = 0.02;
% for i = 1:length(theta)
%     delta_r_E_SC(i) = sqrt((norm(R_E/(1-cosd(theta(i))) * r_SC_E * delta_theta))^2);
% end