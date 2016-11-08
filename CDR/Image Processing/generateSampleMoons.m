%% Anthony Torres
% OSPRE
% generateSampleMoons.m
% Created: 10/27/16
%
% Purpose: Generates a set of test images along with the corresponding data
%
% Inputs:
%   None
%
% Outputs:
%   Images of different phases of moon
%   Datafiles containing center point data, and percent illumination data
%
%

m = 4192;
n = 3104;
min_ang_dia = 0.88; %deg
resolution = 72; %pix/deg
moonPxRad = round(min_ang_dia*resolution);
moonX = n/2;
moonY = m/2;
circDist = 1.5*moonPxRad;
rOverlap = round(linspace(moonPxRad, 2.5*moonPxRad, 10));

centerPointData = zeros(length(rOverlap),2);
percentIllumData = zeros(length(rOverlap),1);

tic
for i = 1:length(rOverlap)
    [CenterPoints,im] = Circle_2D_Overlap(m,n,moonX, moonY, moonPxRad, rOverlap(i), circDist);

    % Save image
    imFilename = sprintf('OSPRE/Sample Images/GenImages/im%d.jpg', i);
    imwrite(im, imFilename, 'jpg');
    
    centerPointData(i,:) = CenterPoints;
    percentIllumData(i) = percentIllum(moonPxRad, rOverlap(i), circDist);
end

toc
% Save center points
save('OSPRE/Sample Images/GenImages/centerPoints.mat', 'centerPointData');
% Save percent illumination data
save('OSPRE/Sample Images/GenImages/percentIllumData.mat', 'percentIllumData');