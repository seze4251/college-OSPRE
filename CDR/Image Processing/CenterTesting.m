

close all; clear all;

profile on;
%% Load image
%=== Lots of comments for different test cases ===
% im = imread('FullMoon2010-Med.jpg');
i = 1; % This is used for generated images
% imFilename = sprintf('OSPRE/Sample Images/GenImages/im%d.jpg',3);
% im = imread(imFilename);
im = imread('OSPRE/Sample Images/FeltTest/IMG_19700101_004100.jpg');

% Convert to gray and pull out dimensions
im = convertGray(im);
dim = size(im);
rngX = 1:1:dim(1);
rngY = 1:1:dim(2);

% Convert to BW, hreshold, and fill image
bw = imfill(imbinarize(im),'holes');

% Find circle fit through CHT
% Set +/- radius range
dRadius = 5; %round(10/67*321);
% Set ideal radius
idealRadius = 321;
% Create radius range
radiusRange = [floor(idealRadius-dRadius) round(idealRadius+dRadius)];

% Find dat circle
[centers, radii] = imfindcircles(bw, radiusRange, 'Sensitivity', 0.99)

% Assert that there is at least one circle, or quit
if(isempty(centers))
    warning('No centers!')
    return;
end

% Load center point data for error calcs
if(~debugOn)
    load('OSPRE\Sample Images\GenImages\centerPoints.mat');
    yErr = centerPointData(i,1) - centers(2);
    xErr = centerPointData(i,2) - centers(1);

    fprintf('x-Error: %.4f\ty-Error: %.4f\n', xErr, yErr)
end

%% Calculate accumulator matrix
[accumMatrixBW, gradientImgBW] = calcAccum(bw, radiusRange);
% Normalize votes, collapsing 3D to 2D
normVotes = abs(mean(accumMatrixBW))./max(abs(mean(accumMatrixBW)));

% Fit data, NOT USED RIGHT NOW
dataFit = fit(rngY', normVotes', 'gauss1');
newY = linspace(rngY(1), rngY(end));
fitOutput = dataFit(rngY);

%% Plot 2D votes
figure(1)
hold on;
plot(rngY, normVotes, '*:b')
vline(dim(2)/2, '--g');     % True center
vline(centers(1), '-.r');   % Calculated
% plot(rngY, fitOutput, '+-k') % Disabled Gauss fit
grid on; grid minor;
if(~debugOn)
    legend('Votes', 'True Center', 'Calculated', 'Gauss Fit', 'location', 'NorthEast');
    legend('Votes', 'True Center', 'Calculated', 'location', 'NorthEast');
    set(gca, 'xlim', [dim(2)/2-50 dim(2)/2+50]);
end
xlabel('x-pixels'); ylabel('Normalized Votes');

if(~debugOn)
    clippedX2 = (dim(1)/2-75):(dim(1)/2+75);
    clippedY2 = (dim(2)/2-75):1:(dim(2)/2+75);
    surf(rngY(clippedY2), rngX(clippedX2), abs(accumMatrixBW( clippedX2, clippedY2)), 'LineStyle', 'none')
end

%% Plot contour map of accumulator matrix
figure(2)
% image(im); % Tried to add image to bottom x-y plane, work in progress

hold on;
contourf(rngY, rngX,abs(accumMatrixBW), 'linestyle', 'none')

if(~debugOn)
    dClipped = 50;
    clippedY = (dim(2)/2-dClipped):1:(dim(2)/2+dClipped);
    clippedX = (dim(1)/2-dClipped):(dim(1)/2+dClipped);
    contourf(rngY( clippedY ), ...
             rngX( clippedX ), ...
             abs(accumMatrixBW( clippedX, clippedY)), ...
             'linestyle', 'none')
    plot(centerPointData(i,2), centerPointData(i,1), '^g');
end
plot(centers(1), centers(2), '*r');

% Plot midlines
line([dim(2)/2 dim(2)/2], [0 dim(1)], 'Color', 'c'); % Vertical line
line([0 dim(2)], [dim(1)/2 dim(1)/2], 'Color', 'c') % Horizontal line
hold off

colorbar;
grid on; grid minor;
if(~debugOn)
    set(gca, 'xlim', [dim(2)/2-dClipped dim(2)/2+dClipped], 'ylim', [dim(1)/2-dClipped dim(1)/2+dClipped]);
end
xlabel('x (px)'); ylabel('y (px)');

if(printingOn)
    print('-r200', '-dpng', 'OSPRE/Radius Range Eval/3RadRng');
end

%% Plot circle overlay
figure(3);
imshow(im);
hold on;
line([dim(2)/2 dim(2)/2], [0 dim(1)], 'Color', 'c', 'linewidth', 1.5); % Vertical line
line([0 dim(2)], [dim(1)/2 dim(1)/2], 'Color', 'c', 'linewidth', 1.5) % Horizontal line

viscircles(centers, radii,'EdgeColor','b');
if(~debugOn)
    scatter(centers(:,1), centers(:,2), 'MarkerEdgeColor',[.5 0 .5],...
                  'MarkerFaceColor',[1 0 1],...
                  'LineWidth',1.5)
    plot(centerPointData(i,2), centerPointData(i,1), '^g');
end
plot(centers(1), centers(2), '*r');
hold off;

if(~debugOn)
    message = sprintf(['Calculated Center: (%.2f, %.2f) pixels\n'...
                      'Actual Center: (%.2f, %.2f) pixels\n'...
                      'x-Error: %.4f px, y-Error: %.4f px'], centers(1,1), centers(1,2), ...
                      centerPointData(i,2), centerPointData(i,1), xErr, yErr);
else
    message = sprintf(['Calculated Center: (%.2f, %.2f) pixels'], centers(1,1), centers(1,2));
end

text(50,120,message,'Color','y','FontWeight','bold');


if(printingOn)
    print('-r200', '-dpng', 'OSPRE/verifyImage_102616')
end