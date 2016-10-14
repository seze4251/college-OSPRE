function [error_range, range] = Earth_Range_Position_Error(alpha, beta, sigma_mean)
%%% Calculates the error matrix for the Earth ranging algorithm
%
% Inputs:   alpha       Horizontal quaternion error angle   (deg)
%           beta        Vertical quaternion error angle     (deg)
%           simga_mean  Degree measurement error (deg)
%
% Outputs:  error_range - n x m error matrix with n representing the
%                         sigma_mean and m representing the spacecraft 
%                         range from Earth. Range error in km.
% Author:   Cameron Maywood
% Created:  10/3/2016
% Modified: 10/3/2016
%
%%
% Import SC ECEF data
data = importdata('ECF Position SkyFire.txt');
time = data(:, 1);
x_Pos_ECEF = data(:, 2);
y_Pos_ECEF = data(:, 3);
z_Pos_ECEF = data(:, 4);
pos_ECEF = [x_Pos_ECEF'; y_Pos_ECEF'; z_Pos_ECEF'];
vec_length = length(time);

omega_E = 7.2921150e-5;     % Earth rotation, rad/s
R_E = 6378.137;             % Earth radius, km

for i = 1:vec_length
    GST(i) = rad2deg(time(i)*omega_E);                      % GST
    pos_ECI(:,i) = ECEF_to_ECI(pos_ECEF(:,i), GST(i));      % ECI position
    range(i) = norm(pos_ECI(:,i));                          % ECI range
    theta_known(i) = 2*atand(R_E/range(i));                 % Angular diameter
    r_SC_E(:,i) = -pos_ECI(:,i)/norm(pos_ECI(:,i));         % Perfect SC attitude unit vector                               
end

% Rotation to make attitude incorrect by alpha and beta
ROT = [cosd(alpha)*cosd(beta),    -sind(alpha),   cosd(alpha)*sind(beta);
       sind(alpha)*cosd(beta),     cosd(alpha),   sind(alpha)*sind(beta);
       -sind(beta),                 0,              cosd(beta)];

% Impefect attitude
for i = 1:vec_length
    r_SC_E(:,i) = inv(ROT)*r_SC_E(:,i);
end

% Calculated position, range, and error using imperfect attitude and angle error
for i = 1:length(sigma_mean)
    for j = 1:vec_length
        pos_Calc(:,j,i) = Position_From_Earth_Range_Vec(r_SC_E(:,j), alpha+sigma_mean(i), beta+sigma_mean(i), theta_known(j)+sigma_mean(i));
        range_calc(i,j) = norm(pos_Calc(:,j,i));
        error_range(i,j) = abs(range(j) - range_calc(i,j));
    end
end

end