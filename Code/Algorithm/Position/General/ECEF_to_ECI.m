function [r_ECI] = ECEF_to_ECI(r_ECEF, theta_GST)
%%% Calculates the position in ECI given the Greenwich sidereal time and
%%% position in ECEF using equation:
%%% r_ECI = ROT3(theta_GST)^-1*r_ECEF

%% Rotation matrix
ROT3 = [cosd(-theta_GST) sind(-theta_GST) 0; 
        -sind(-theta_GST)  cosd(-theta_GST) 0;
        0               0              1];
 
%% Solve
r_ECI = ROT3*r_ECEF;
 
end