%% Cameron Maywood, Anthony Torres, Seth Zegelstein
% calcRminErr.m
% Created: 10/3/16
% Modified: 10/3/16
% 
% % Description:
%   Calculates the minimum error of the three methods, Rerr1, Rerr2, and
%   Rerr3, such that the output is n x m with the same n x m as the inputs,
%   and each cell value is the minimum error of the three methods.
%
% Assumptions:
%   Input matrices are defined and do not contain any NaN or Inf
%   Inputs are real
%
%
% Inputs:
%   Rerr1 --- Earth, minimum error matrix for ranging at Earth for
%   different degree errors and at different locations. Dimensions: n x m 
%   where n = degree error (deg), m = positions (km), with cell values in km
%
%   Rerr2 --- Moon, minimum error matrix for ranging at Moon for
%   different degree errors and at different locations. Dimensions: n x m 
%   where n = degree error (deg), m = positions (km), with cell values in km
%
%   Rerr3 --- Angles, minimum error matrix for angles-only position
%   detection, Dimensions: n x m where n = degree error (deg), m =
%   positions (km), with cell values in km
%
%
% Outputs:
%   Rmin --- n x m matrix with the same n x m as the inputs,
%   and each cell value is the minimum error of the three methods Rerr1,
%   Rerr2, Rerr3
%
%   MethodMin --- n x m matrix with the same n x m as the inputs, and each
%   cell value is either 1, 2, 3 representing the method that resulted in
%   the least error with 1 = first input, 2 = second input, etc.
%
% TODO:
%   Rearrange for variable number of input n x m arrays

function[Rmin, MethodMin] = calcRminErr(Rerr1, Rerr2, Rerr3)

% Initialize variables
dim = size(Rerr1);
MethodMin = zeros(dim);
Rmin = zeros(dim);

% Double for-loop to iterate through n and m dimensions of the matrix
for i = 1:dim(1)
    for j = 1:dim(2)
        % Find the min value and its index
        [minTmp, minInd] = min([Rerr1(i,j), Rerr2(i, j), Rerr3(i, j)]);
        % Set the values of the corresponding matrices
        Rmin(i, j) = minTmp;
        MethodMin(i, j) = minInd;
    end
end

end