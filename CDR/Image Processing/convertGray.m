%% Anthony Torres
% convertGray.m
% OSPRE
% Created: 11/15/16
% Modified: 11/15/16
%
% Purpose: Converts an input image to grayscale with equal R,G,B weighting
%
% Inputs:
%   imIn --- RGB image
%
% Outputs:
%   imOut --- grayscale image

function[imOut] = convertGray(imIn)

% Verifiy that image is RGB, otherwise return the input image
imDim = size(imIn);
if(length(imDim) < 3)
    imOut = imIn;
    return;
end

% Pull out each R,G,B layer
R = imIn(:,:,1);
G = imIn(:,:,2);
B = imIn(:,:,3);

% Output data
imOut = 0.333*R + 0.333*G + 0.333*B;
end