function [ v_error ] = velocityError( r_error )
% Seth Zegelstein
% Date Created: 9/27/2016
% Date Modified:
% Inputs:
% r_error: A n by m matrix of the smallest position errors from the three
% methods. Each row represents a certin accuracy of image proccessing and
% each column represents distance from the earth
% Outputs:
% v_error: A n by m-1 matrix of velocity errors for different image
% proccessing accuracies and at different distances
% Description: Takes in r_error computes the velocity error for the given
% position errors
% Assumptions: Assumes that every velocity measurment is taken at 1 hour
% intervals

n = size(r_error,1);
m = size(r_error,2);
deltaT = 3600;    % seconds
v_error = zeros(n , m-1);

for i = 1 : n
    for j = 1 : m -1
        v_error(i,j) = sqrt((r_error(i,j)/deltaT)^2 + (r_error(i, j+1) / deltaT)^2 );
    end
end
end

