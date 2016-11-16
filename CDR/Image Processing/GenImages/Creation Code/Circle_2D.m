function [CenterPoints,RGB_MATRIX1,RGB_MATRIX2] = Circle_2D(m,n,min_ang_dia,resolution, rOverlap, vargin)
% Author: Zachary Folger
% Modified: Anthony Torres 10/26/16
% Date: 10/26/16
% Inputs:   m - number of horizontal pixels (property of camera sensor)
%           n - number of vertical pixels (property of camera sensor)
%           min_ang_dia - angular diameter of celestial body (deg)
%           resolution - resolution of camera in choice (pix/deg)
%           filename1,2,3 - filename to save image1 (1), image2 (2), and
%           the center point data (3)

% Outputs:  CenterPoints - The X and Y pixel values for center values of
%           both images. For verification of image processing.
%           RGB_MATRIX1,2 - 3 dimensional RGB matrix logic values

saveImg = 0;
if(nargin>4)
    filename1 = vargin(1);
    filename2 = vargin(2);
    filename3 = vargin(3);
    saveImg = 1;
end

radius = min_ang_dia*resolution;

B = zeros(n,m);
G = zeros(n,m);
R = zeros(n,m);

% Figure 1:
% figure;
im1 = zeros(n,m,3);
im1(:,:,1) = MidpointCircle(R,radius,n/2,m/2,1);
im1(:,:,2) = MidpointCircle(G,radius,n/2,m/2,1);
im1(:,:,3) = MidpointCircle(B,radius,n/2,m/2,1);

if(min(rOverlap))
RGB_MATRIX1 = im1;%cat(3,R_circ,G_circ,B_circ);
% im1 = image(RGB_MATRIX1);
if(sameImg)
imwrite(im1,filename1,'jpg','Comment','My JPEG file')
end

% figure;
im2 = zeros(n,m,3);
im2(:,:,1) = MidpointCircle(R,radius,m/2,n/2,1);
im2(:,:,2) = MidpointCircle(G,radius,m/2,n/2,1);
im2(:,:,3) = MidpointCircle(B,radius,m/2,n/2,1);
RGB_MATRIX2 = im2;%cat(3,R_circ,G_circ,B_circ);
% im2 = image(RGB_MATRIX2);
if(sameImg)
imwrite(im2,filename2,'jpg','Comment','My JPEG file')
end

CenterPoints = [n/2,m/2;m/2,n/2];

if(sameImg)
save(filename3, 'CenterPoints');
end

end

