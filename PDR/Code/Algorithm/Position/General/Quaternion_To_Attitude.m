function [r_SC_body] = Quaternion_To_Attitude(q)
%%% Calculates the spacecraft attitude unit vector in ECI.
%
% Inputs:   q   Quaternion  (vector)
%
% Author:   Cameron Maywood
% Created:  9/29/2016
% Modified: 9/29/2016
%
%%
%%% Direct cosine matrix from quaternion
DCM = [q(1)^2 + q(2)^2 - q(3)^2 - q(4)^2,   2*(q(2)*q(3) - q(4)*q(1)),          2*(q(2)*q(4) + q(3)*q(1));
       2*(q(2)*q(3) + q(4)*q(1)),           q(1)^2 - q(2)^2 + q(3)^2 - q(4)^2,  2*(q(3)*q(4) - q(2)*q(1));
       2*(q(2)*q(4) - q(3)*q(1)),           2*(q(3)*q(4) + q(2)*q(1)),          q(1)^2 - q(2)^2 - q(3)^2 + q(4)^2];

%%% Initial ECI frame (assumed to be pointing in the inertial X-axis direction)
r_initial = [1; 0; 0];

%%% Spacecraft attitude vector in ECI
r_SC_body = DCM*r_initial;

end

