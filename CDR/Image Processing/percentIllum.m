%% Anthony Torres
% OSPRE
% percentIllum.m
% Created: 10/27/16
%
% Purpose: Calculated the percent illumination of a disk based on the
%   intersection area of two circles
%   Formula pulled from: http://mathworld.wolfram.com/Circle-CircleIntersection.html
%
% Inputs:
%   R --- main circle (Moon) diameter
%   r --- overlap circle diameter
%   d --- distance between centers
%
% Outputs:
%
% Assumptions:
%

function[pIllum] = percentIllum(R, r, d)

% Calculate area of lens
Alens = r.^2.*acos((d.^2+r.^2-R.^2)./(2.*d.*r)) + ... 
    R.^2.*acos((d.^2+R.^2-r.^2)/(2.*d.*R)) - ...
    0.5.*sqrt((-d+r+R).*(d+r-R).*(d-r+R).*(d+r+R));

Acirc = pi.*R.^2;

pIllum = (Acirc-Alens)./Acirc.*100;

end