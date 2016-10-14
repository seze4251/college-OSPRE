function [r_E_SC] = Position_From_Earth_Range_Vec(r_SC_E, alpha, beta, theta)
%%% Calculates the spacecraft position vector in ECI.
%
% Inputs:   r_SC_E  Spacecraft_Earth attitude unit vector   
%           alpha   Horizontal quaternion error angle       (deg)
%           beta    Vertical quaternion error angle         (deg)
%           theta   Moon angular diameter                   (deg)
%
% Outputs:  r_E_SC  Spacecraft ECI position vector          (km)
%
% Author:   Cameron Maywood
% Created:  10/3/2016
% Modified: 10/3/2016
%
%%
%%% Earth radius, km
R_E = 6378.137;

%%% X component of ECI position vector
r_E_SC(1) = (R_E/tand(theta/2))*(r_SC_E(2)*sind(alpha)-cosd(alpha)*(r_SC_E(1)*cosd(beta)+r_SC_E(3)*sind(beta)));

%%% Y component of ECI position vector
r_E_SC(2) = (-R_E/tand(theta/2))*(r_SC_E(2)*cosd(alpha)+sind(alpha)*(r_SC_E(1)*cosd(beta)+r_SC_E(3)*sind(beta)));

%%% Z component of ECI position vector
r_E_SC(3) = (R_E/tand(theta/2))*(-r_SC_E(3)*cosd(beta) + r_SC_E(1)*sind(beta));

end
