%% Cameron Maywood, Anthony Torres, Seth Zegelstein
% calcMaxDegErr.m
% Created: 10/3/16
% Modified: 10/3/16
% 
% % Description:
%   Calculates the minimum error of the three methods, Rerr1, Rerr2, and
%   Rerr3, such that the output is n x m with the same n x m as the inputs,
%   and each cell value is the minimum error of the three methods.
%
%
% Assumptions:
%   Input variables are defined and do not contain any NaN or Inf
%   Inputs are real
%
%
% Inputs:
%   PosErr --- Matrix containing error values for position, n x m where n =
%   degree error (deg), m = position (km), with cell values in km
%
%   VelErr --- Matrix containing error values for position, n x m where n =
%   degree error (deg), m = position (km), with cell values in m/s
%
%   targetPosErr --- target position error (km)
%
%   targetVelErr --- target velocity error (m/s)
%
%
% Outputs:
%   minAllowDeg --- INDEX of minimum degree error value while staying 
%   within bounds, %   pos = +/- 1000km and vel = +/- 250 m/s. 0 means it
%   failed
%
%   success --- boolean 0 or 1 value indicating if we're within bounds. 0
%   means nothing resulted in error less than our required tolerances
%
%
% TODO:
%   

function[minAllowDeg, success] = calcMaxDegErr(posErr, velErr, targetPosErr, targetVelErr)
% Initialize variables
% If the loop failes, these will be returned to indicate failure
minAllowDeg = 0;
success = 0;

%This way does not take into account the last position error?
% Iterate row by row
for i = 1:length(posErr(:,1))
    % Test if the next row in the loop surpasses the specified error values
    % If the next row does, then set the values to the current row and
    % return
    if(max(posErr(i,:)) < targetPosErr && max(velErr(i,:))  < targetVelErr)
        minAllowDeg = i;
        success = 1;
    else 
        return;
    end
end