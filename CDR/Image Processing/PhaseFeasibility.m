%% Anthony Torres
% PhaseFeasibility.m
% OSPRE
% Created: 10/27/16
%
% Purpose: Analyzes a set of test images to determine error for phases of
%   the moon
%

close all; clear all;

plotting = 1;

% Load image
numImages = 10;
sensitivity = 0.9:0.01:0.99;
load('G:\Users\Anthony\Documents\MATLAB\OSPRE\Sample Images\GenImages\centerPoints.mat');
load('G:\Users\Anthony\Documents\MATLAB\OSPRE\Sample Images\GenImages\percentIllumData.mat');

totalError = -1*ones(numImages, 2, length(sensitivity));
timeEllapsed = zeros(numImages, length(sensitivity));

for j = 1:length(sensitivity)
    for i = 1:numImages
        tic;
        imFilename = sprintf('OSPRE/Sample Images/GenImages/im%d.jpg',i);
        im = imread(imFilename);
        im = rgb2gray(im);
        dim = size(im);
        rngX = 1:1:dim(1);
        rngY = 1:1:dim(2);

        % Convert to BW, hreshold, and fill image
        bw = imfill(imbinarize(im),'holes');

        % Find circle fit through CHT
        radiusRange = [floor(64-2) round(64+2)];
        [centers, radii] = imfindcircles(bw, radiusRange, 'Sensitivity', sensitivity(j));

        if(isempty(centers))
            warning('No centers!')
            timeEllapsed(i, j) = toc;
%             continue;
        end

        yErr = abs(centerPointData(i,1) - centers(2));
        xErr = abs(centerPointData(i,2) - centers(1));

        fprintf('x-Error: %.4f\ty-Error: %.4f\n', xErr, yErr)
        totalError(i, 1, j) = xErr; totalError(i,2,j) = yErr;
        timeEllapsed(i, j) = toc;

        if(plotting)
            [accumMatrixBW, gradientImgBW] = calcAccum(bw, radiusRange);
            normVotes = abs(mean(accumMatrixBW))./max(abs(mean(accumMatrixBW)));

            % Fit data
            dataFit = fit(rngY', normVotes', 'gauss1');
            newY = linspace(rngY(1), rngY(end));
            fitOutput = dataFit(rngY);

            figure
            hold on;
            plot(rngY, normVotes, '*:b')
            vline(dim(2)/2, '--g');     % True center
            vline(centers(1), '-.r');   % Calculated
            % plot(rngY, fitOutput, '+-k') % Disabled Gauss fit
            grid on; grid minor;
            % legend('Votes', 'True Center', 'Calculated', 'Gauss Fit', 'location', 'NorthEast');
            legend('Votes', 'True Center', 'Calculated', 'location', 'NorthEast');
            set(gca, 'xlim', [dim(2)/2-50 dim(2)/2+50]);
            xlabel('x-pixels'); ylabel('Normalized Votes');

            % clippedX2 = (dim(1)/2-75):(dim(1)/2+75);
            % clippedY2 = (dim(2)/2-75):1:(dim(2)/2+75);
            % surf(rngY(clippedY2), rngX(clippedX2), abs(accumMatrixBW( clippedX2, clippedY2)), 'LineStyle', 'none')

            figure
            % image(im); 
            clippedY = (dim(2)/2-15):1:(dim(2)/2+15);
            clippedX = (dim(1)/2-15):(dim(1)/2+15);
            hold on;
%             contourf(rngY, rngX,abs(accumMatrixBW), 'linestyle', 'none')
            contourf(rngY( clippedY ), ...
                     rngX( clippedX ), ...
                     abs(accumMatrixBW( clippedX, clippedY)), ...
                     'linestyle', 'none')
            plot(centerPointData(i,2), centerPointData(i,1), '^g');
            plot(centers(1), centers(2), '*r');

            line([dim(2)/2 dim(2)/2], [0 dim(1)], 'Color', 'c'); % Vertical line
            line([0 dim(2)], [dim(1)/2 dim(1)/2], 'Color', 'c') % Horizontal line
            hold off

            colorbar;
            grid on; grid minor;
            set(gca, 'xlim', [dim(2)/2-10 dim(2)/2+10], 'ylim', [dim(1)/2-10 dim(1)/2+10]);
            xlabel('x (px)'); ylabel('y (px)');

            figure;
            imshow(im);
            hold on;
            line([dim(2)/2 dim(2)/2], [0 dim(1)], 'Color', 'c', 'linewidth', 1.5); % Vertical line
            line([0 dim(2)], [dim(1)/2 dim(1)/2], 'Color', 'c', 'linewidth', 1.5) % Horizontal line

            % Plot the circles on top
            viscircles(centers, radii,'EdgeColor','b');
            % scatter(centers(:,1), centers(:,2), 'MarkerEdgeColor',[.5 0 .5],...
            %               'MarkerFaceColor',[1 0 1],...
            %               'LineWidth',1.5)
            plot(centerPointData(i,2), centerPointData(i,1), '^g');
            plot(centers(1), centers(2), '*r');
            hold off;

            message = sprintf(['Calculated Center: (%.2f, %.2f) pixels\n'...
                              'Actual Center: (%.2f, %.2f) pixels\n'...
                              'x-Error: %.4f px, y-Error: %.4f px'], centers(1,1), centers(1,2), ...
                              centerPointData(i,2), centerPointData(i,1), xErr, yErr);
            text(50,120,message,'Color','y','FontWeight','bold');

            % print('-r200', '-dpng', 'OSPRE/verifyImage_102616')
            fprintf('Press a key to continue...\n')
            pause
        end
    end
end

% Create array of marker styles
plotMarkerStyle = ['o'; '+'; '*'; '.'; 's'; 'x'; 'd'; '^'; 'v'; '>'; '<'; 'p'; 'h'];

% Separate out the x component
xErr = squeeze(totalError(:,1,:));
xErr(xErr == -1) = NaN;
  
yErr = squeeze(totalError(:,2,:));
yErr(yErr == -1) = NaN;
yErr(7,end) = NaN;

for k = 1:length(sensitivity)
    figure(1)
    hold on;
    ax1(k) = plot(real(percentIllumData), xErr(:,k), 'Marker', plotMarkerStyle(k));
    set(gca, 'xdir', 'reverse')
    grid on; grid minor;
    xlabel('Percent Visible'); ylabel('Absolute Difference Error (px)');
    title('X Error')
    
    figure(2)
    hold on;
    ax2(k) = plot(real(percentIllumData), yErr(:,k), 'Marker', plotMarkerStyle(k));
    set(gca, 'xdir', 'reverse')
    grid on; grid minor;
    xlabel('Percent Visible'); ylabel('Absolute Difference Error (px)');
    title('Y Error')
end

legend(ax1, {'0.90', '0.91', '0.92', '0.93', '0.94', '0.95', '0.96', '0.97', '0.98', '0.99'}, 'location', 'North');
legend(ax2, {'0.90', '0.91', '0.92', '0.93', '0.94', '0.95', '0.96', '0.97', '0.98', '0.99'}, 'location', 'North');

figure(3)
surf(real(percentIllumData), sensitivity, timeEllapsed)
xlabel('Percent Visible'); ylabel('Sensitivity');
zlabel('Time Ellapsed (s)')
title({'Time Ellapsed for Phase Analysis','AMD FX8350'})

print(figure(1), '-r200', '-dpng', 'OSPRE/phaseSensX');
print(figure(2), '-r200', '-dpng', 'OSPRE/phaseSensY');
print(figure(3), '-r200', '-dpng', 'OSPRE/Sample Images/phaseFeasTimeEllapsed')