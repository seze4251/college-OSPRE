% Cameron Maywood, Anthony Torres, Seth Zegelstein
% Date Created: 9/27/2016
% % Date Modified:
% Purpose: Main Script for PDR
close all; clc;

%% Camera 1 18 degree FOV, 13 Mega Pixels
% clearvars;
% 
% pixels = 13011968; %pixels
% FOV = [18 18]; %degrees
% plots = 3; % Show Plots
% pixPerDeg = 0; % Use pixel and FOV in calculations
% plotStr{1} = sprintf('Position Error vs Distance for ZenFone Zoom Camera');
% plotStr{2} = sprintf('Velocity Error vs Distance for ZenFone Zoom Camera');
% pixel_error_vec = linspace(2,50,100);
% [validSolution, minDegAccuracy] = PositionVelocityError( pixels, FOV, plots, pixPerDeg, plotStr, pixel_error_vec );
% 
% if validSolution == 0
%     str = 'a valid solution.';
% else
%     str = 'a invalid solution.';
% end
% 
% fprintf('This option is %s Image processing must be accurate to within %.5f degrees \n in order to meet requirments for top choice \n camera within volume constraints \n', str, minDegAccuracy);

%% Create Maximum Image Error vs pixel/deg plot
% clearvars;
% 
pixels = []; %pixels
FOV = []; %degrees
plots = 0; % Show Plots
plotStr = [];
pixPerDeg = linspace(1,250,40); % Use pixel and FOV in calculations
pixel_error_vec = linspace(1,1000,1000);
count = 1;

for i = pixPerDeg
    [validSolution, minDegAccuracy(count)] = PositionVelocityError( pixels, FOV, plots, [i i], plotStr, pixel_error_vec );
    count = count + 1;
end

figure;
plot(pixPerDeg, minDegAccuracy)
xlabel 'Pixel/Degree'
ylabel 'Maximum Allowable Degree Error From Image Processing (Degree)'
tit = sprintf('Maximum Image processing Error vs Pixel/Degree \n required for a valid solution');
title(tit);

% Create Maximum Position/ Velocity Error vs Image Processing Error
clearvars;

count = 1;
sigma_eff = linspace(0.01,.06,1000);
[r_error, v_error] = PosVelError2( sigma_eff );

for i = 1 : length(sigma_eff)
    MaxPosError(i) = max(r_error(i,:));
    MaxVelError(i) = max(v_error(i,:));
end

figure;
subplot(1,2,1)
hold on
plot(sigma_eff, MaxPosError)
plot(sigma_eff,1000*ones(length(sigma_eff)), '--')
xlabel 'Degree Error'
ylabel 'Maximum Position Error (km)'
ylim([0 1300])
tit = sprintf('Position Error vs Degree Error');
title(tit);
hold off

subplot(1,2,2)
hold on
plot(sigma_eff, MaxVelError)
plot(sigma_eff,250*ones(length(sigma_eff)), '--')
xlabel 'Degree Error'
ylabel 'Maximum Velocity Error (m/s)'
ylim([0 350])
tit = sprintf('Velocity Error vs Degree Error');
title(tit);
hold off

ind = find(MaxVelError > 250);
maxDegError = sigma_eff(ind(1)-1);
%% Relate Pixel / Degree to degree Error
close all; clc; clearvars -except maxDegError;


pixelperdeg = linspace(3,250,1000);
pixelerror = linspace(.2,4,6);

figure;
hold on
for i = 1 : length(pixelerror)
    sigma = 1 ./ pixelperdeg * pixelerror(i);
    plot(pixelperdeg, sigma)
    str{i} = sprintf('Pixel Error %1.2f', pixelerror(i));
end
legend(str)
plot(pixelperdeg, maxDegError * ones(length(pixelperdeg)),'k--')
ylim([0 0.05])
xlabel 'Pixel Per Degree'
ylabel 'Degree Error (deg)'
tit = sprintf('Degree Error vs Pixel Per Degree \n for Various Amounts of Pixel Error');
title(tit)
hold off




