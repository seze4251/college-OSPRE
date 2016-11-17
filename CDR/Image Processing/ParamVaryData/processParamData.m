%% Anthony Torres
% processParamData.m
% OSPRE
% Created:  11/1/16
% Modified: 11/3/16
%
% Purpose: Analyzes a set of test images to find the optimum parameters for
% the circle search
%

close all;

totErrPt3 = load('OSPRE/ParamVaryData/totalError_Part3.mat');
timeEllapsedPt3 = load('OSPRE/ParamVaryData/timeEllapsed_Part3.mat');
sensPt3 = load('OSPRE/ParamVaryData/sensitivity_Part3.mat');
radiusRngPt3 = load('OSPRE/ParamVaryData/radiusRng_Part3.mat');

% load('OSPRE/ParamVaryData/totalError_Part2.mat');
% load('OSPRE/ParamVaryData/timeEllapsed_Part2.mat');
% load('OSPRE/ParamVaryData/sensitivity_Part2.mat');
% load('OSPRE/ParamVaryData/radiusRng_Part2.mat');

totErrPt1 = load('OSPRE/ParamVaryData/totalError.mat');
timeEllapsedPt1 = load('OSPRE/ParamVaryData/timeEllapsed.mat');
sensPt1 = load('OSPRE/ParamVaryData/sensitivity.mat');
radiusRngPt1 = load('OSPRE/ParamVaryData/radiusRng.mat');

radiusRng = 1:68;

sensitivity = sensPt1.sensitivity;
% sensitivity = zeros(1,length(sensPt1.sensitivity)+length(sensPt3.sensitivity));
% sensitivity(1:length(sensPt1.sensitivity)) = sensPt1.sensitivity;
% sensitivity(length(sensPt1.sensitivity)+1:length(sensPt3.sensitivity)) = sensPt3.sensitivity;

totalError = zeros(10, 2, 40, 68);
totalError(:,:,:,1:10) = totErrPt1.totalError;
totalError(:,:,:,11:68) = totErrPt3.totalError;

xTotalError = zeros(length(sensitivity),length(radiusRng));
yTotalError = xTotalError;

% Remove -1 values
% xTotalError(xTotalError == -1) = NaN;
% yTotalError(yTotalError == -1) = NaN;
% totalError(totalError == -1) = NaN;
totalError(totalError == -1) = NaN;

for i = 1:length(sensitivity)
    for j = 1:length(radiusRng)
        tmp = nanmean(totalError(:,:,i,j));
        xTotalError(i,j) = tmp(1);
        yTotalError(i,j) = tmp(2);
    end
end

%% Plot the x pixel error
figure(1)
hold on
surf(sensitivity, radiusRng, xTotalError') % 'LineStyle','none'
patch([0.6 1 1  0.6], ...
      [0   0 56 56], ...
      [0 0 0 0], ...
      [1 1 -1 -1], 'FaceAlpha', 0.3) 
hold off;
grid on; grid minor;
view(-106, 34)
set(gca, 'ylim', [0 56])
xlabel('Sensitivity'); ylabel('\pm Radius');
zlabel('Error (px)');
title('X-Error')

%% Plot the y pixel error
% yTotalError(yTotalError > 50) = NaN;

figure(2)
surf(sensitivity, radiusRng, yTotalError')
patch([0.6 1 1  0.6], ...
      [0   0 56 56], ...
      [0 0 0 0], ...
      [1 1 -1 -1], 'FaceAlpha', 0.3) 
hold off;
grid on; grid minor;
view(-144, 28)
set(gca, 'ylim', [0 56])
xlabel('Sensitivity'); ylabel('\pm Radius');
zlabel('Error (px)');
title('Y-Error')


%% Print
% print(figure(1), '-r200', '-dpng', 'OSPRE/ParamVaryData/xPxError');
% print(figure(2), '-r200', '-dpng', 'OSPRE/ParamVaryData/yPxError');