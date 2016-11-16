%% Anthony Torres
% findCircle.m
% OSPRE
% Created: 11/15/16
% Modified: 11/15/16
%
% Purpose: Finds a circle for a given image
%
% Inputs:
%   imIn --- input image, can be RGB or Gray
%
%   vargin --- optional arguments to modify algorithm
%       radiusRng --- radius range, needs to be whole integers
%       sens --- sensitivity value, Range: [0, 1] floats/doubles
%
% Outputs:
%   center --- [2x1] center pixel coordinate
%
%   radiusOut --- [1x1] radius output

function[centerOut, radiusOut] = findCircle(imIn, varargin)
%% Initialize variables
if(nargin > 1)
    radiusRng = varargin{1};
    sens = varargin{2};
else
    % These parameters are optimized for worst case 0.88 deg angular
    % diameter, and 67 px/deg resolution
    radiusRng = 10;
    sens = 0.99;
end

imDim = size(imIn);

%% Pre-process image
% Convert to grayscale with equal R,G,B weighting
if(length(imDim) > 2)
    bw = convertGray(imIn);
else
    bw = imIn;
end

% Threshold/binarize image, only if passed an RGB image, and fill 
% any potential holes
%
% The hole filling will work better for higher detail images where certain
% features will be darker - like patches
bw = imfill(imbinarize(bw),'holes');

%% Find circle(s)
% Should only be one circle in image, but will choose strongest candidate
[centers, radii] = imfindcircles(bw, radiusRng, 'Sensitivity', sens);

% Assert that there are at least one center
if(isempty(centers))
    centerOut = [nan nan]; radiusOut = nan;
    return;
end

% Output data
centerOut = [centers(1,2) centers(1,1)];
radiusOut = radii(1);

end