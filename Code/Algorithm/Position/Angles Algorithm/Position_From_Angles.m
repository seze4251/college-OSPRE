function [r_E_SC] = Position_From_Angles(r_E_M, q_E, q_M, alpha, beta)
%%% Calculates the spacecraft position vector in ECI.
%
% Inputs:   r_E_M   Moon ECI position vector            (km)
%           q_E     Spacecraft-Earth quaternion         (vector)
%           q_M     Spacecraft_Moon quaternion          (vector)
%           alpha   Horizontal quaternion error angle   (deg)
%           beta    Vertical quaternion error angle     (deg)
%
% Author:   Cameron Maywood
% Created:  9/29/2016
% Modified: 9/29/2016
%
%%

%%% Quaternion error rotation matrix
ROT_Q = [cosd(alpha)*cosd(beta),    -sind(alpha),   cosd(alpha)*sind(beta);
         sind(alpha)*cosd(beta),     cosd(alpha),   sind(alpha)*sind(beta);
         -sind(beta),                0,             cosd(beta)];

%%% Spacecraft-Earth attitude unit vector
r_SC_E = ROT_Q*Quaternion_To_Attitude(q_E);

%%% Spacecraft-Moon attitude unit vector
r_SC_M= ROT_Q*Quaternion_To_Attitude(q_M);

%%% Angle between Earth and Moon
theta_SC = acosd(dot(r_SC_E, r_SC_M));

%%% Earth-Moon distance
d_E_M = norm(r_E_M);

%%% Angle between Earth and spacecraft
theta_M = acosd(dot(-r_E_M, -r_SC_M)/d_E_M);

%%% ECI position vector
r_E_SC = d_E_M*sind(theta_M)/sind(theta_SC)*-r_SC_E;

end

