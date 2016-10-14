function [r_E_SC] = Position_From_Moon_Range(r_E_M, r_SC_M, alpha, beta, theta)
%%% Calculates the spacecraft position vector in ECI.
%
% Inputs:   r_E_M   Moon ECI position vector                (km)
%           r_SC_M  Spacecraft_Moon attitude unit vector
%           alpha   Horizontal quaternion error angle       (deg)
%           beta    Vertical quaternion error angle         (deg)
%           theta   Moon angular diameter                   (deg)
%
% Outputs:   r_E_SC  Spacecraft ECI position vector          (km)
%
% Author:   Cameron Maywood
% Created:  9/29/2016
% Modified: 9/29/2016
%
%%
%%% Moon radius, km
R_M = 1738.1;

%%% X component of Moon-SC position vector
r_M_SC(1) = (R_M/tand(theta/2))*(r_SC_M(2)*sind(alpha)-cosd(alpha)*(r_SC_M(1)*cosd(beta)+r_SC_M(3)*sind(beta)));

%%% Y component of Moon-SC position vector
r_M_SC(2) = (-R_M/tand(theta/2))*(r_SC_M(2)*cosd(alpha)+sind(alpha)*(r_SC_M(1)*cosd(beta)+r_SC_M(3)*sind(beta)));

%%% Z component of Moon-SC position vector
r_M_SC(3) = (R_M/tand(theta/2))*(-r_SC_M(3)*cosd(beta) + r_SC_M(1)*sind(beta));

%%% ECI position vector
r_E_SC = r_E_M + r_M_SC';

end

