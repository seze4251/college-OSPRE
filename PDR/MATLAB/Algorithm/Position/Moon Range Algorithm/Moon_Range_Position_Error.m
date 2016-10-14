function [error_range] = Moon_Range_Position_Error(alpha, beta, sigma_mean)
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

% Import Moon ECEF data
data = importdata('ECF Position Moon.txt');
x_Pos_Moon_ECEF = data(:, 2);
y_Pos_Moon_ECEF = data(:, 3);
z_Pos_Moon_ECEF = data(:, 4);
pos_Moon_ECEF = [x_Pos_Moon_ECEF'; y_Pos_Moon_ECEF'; z_Pos_Moon_ECEF'];

omega_E = 7.2921150e-5;     % Earth rotation, rad/s
R_M = 1738.1;               % Moon radius, km

for i = 1:vec_length
    GST(i) = rad2deg(time(i)*omega_E);                              % GST
    pos_ECI(:,i) = ECEF_to_ECI(pos_ECEF(:,i), GST(i));              % ECI position SC
    pos_Moon_ECI(:,i) = ECEF_to_ECI(pos_Moon_ECEF(:,i), GST(i));    % ECI position Moon
    range(i) = norm(pos_ECI(:,i));                                  % ECI range
    range_Moon(i) = norm(pos_Moon_ECI(:,i)-pos_ECI(:,i));           % ECI range Moon
    theta_known(i) = 2*atand(R_M/range_Moon(i));                    % Angular diameter Moon
    r_SC_M(:,i) = (pos_Moon_ECI(:,i)-pos_ECI(:,i))/norm(pos_Moon_ECI(:,i)-pos_ECI(:,i));       % Perfect SC attitude unit vector                               
end

% Rotation to make attitude incorrect by alpha and beta
ROT = [cosd(alpha)*cosd(beta),    -sind(alpha),   cosd(alpha)*sind(beta);
       sind(alpha)*cosd(beta),     cosd(alpha),   sind(alpha)*sind(beta);
       -sind(beta),                 0,              cosd(beta)];

% Impefect attitude
for i = 1:vec_length
    r_SC_M(:,i) = inv(ROT)*r_SC_M(:,i);
end

% Calculated position, range, and error using imperfect attitude and angle error
for i = 1:length(sigma_mean)
    for j = 1:vec_length
        pos_Calc(:,j,i) = Position_From_Moon_Range_Vec(pos_Moon_ECI(:,j), r_SC_M(:,j), alpha+sigma_mean(i), beta+sigma_mean(i), theta_known(j)+sigma_mean(i));
        range_calc(i,j) = norm(pos_Calc(:,j,i));
        error_range(i,j) = abs(range(j) - range_calc(i,j));
    end
end

end