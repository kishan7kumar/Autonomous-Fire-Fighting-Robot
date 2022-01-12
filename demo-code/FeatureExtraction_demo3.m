%% clearing all garbage
clear all;
clc;
close all;
%% starting logitech camera
cam=webcam(1);                                   % accessing Logi camera to start detecting  flame
%% Loading Images from pc and camera
SignImage = imread('sign2.jpg');
pause(2);
%for loop = 1:50
SceneImage = snapshot(cam);                            %imread('fire2.jpg');
%% converting RGB image to Grayscale images
GraySign= rgb2gray(SignImage);
GrayScene = rgb2gray(SceneImage);
%% plotting features of flame
% figure;
% imshow(GrayFlame);
% hold on;
Signpoints = detectSURFFeatures(GraySign);
%plot(Flamepoints.selectStrongest(100));
%% ploting features of scene
%  figure;
%  imshow(GrayScene);
% hold on;
Scenepoints = detectSURFFeatures(GrayScene);
%plot(Scenepoints.selectStrongest(100));
%% extracting Features
[SignFeatures, Signpoints] = extractFeatures(GraySign, Signpoints);

[SceneFeatures, Scenepoints] = extractFeatures(GrayScene, Scenepoints);
%% Matching features 
FlamePairs = matchFeatures(SignFeatures, SceneFeatures,'MatchThreshold', 90);
%pause(2);
%%  Displaying features lines from subject to scene
matchedSignpoints = Signpoints(FlamePairs(:, 1), :);
matchedScenepoints = Scenepoints(FlamePairs(:, 2), :);
figure;
showMatchedFeatures(GraySign, GrayScene, matchedSignpoints, ...
matchedScenepoints, 'montage');
title('Putatively Matched Points (Including Outliers)');
%% removing extra features lines using geometric transformation
  [tform , inlierFlamepoints, inlierScenepoints] = ...
      estimateGeometricTransform(matchedSignpoints, matchedScenepoints, 'similarity');  
%% Display the matching point pairs with the outliers removed
figure;
showMatchedFeatures(GraySign, GrayScene, inlierFlamepoints, ...
    inlierScenepoints, 'montage');
title('Matched Points (Inliers Only)');

%%Get the bounding polygon of the reference image.
boxPolygon = [1, 1;...                           % top-left
        size(GraySign, 2), 1;...                 % top-right
        size(GraySign, 2), size(GraySign, 1);... % bottom-right
        1, size(GraySign, 1);...                 % bottom-left
        1, 1];                   % top-left again to close the polygon

%%  Transform the polygon into the coordinate system of the target image
  newboxPolygon = transformPointsForward(tform, boxPolygon);
%%  Display the detected object.
figure;
imshow(SceneImage);
hold on;
line(newboxPolygon(:, 1), newboxPolygon(:, 2), 'Color', 'b','LineWidth',4);
title('Detected Room no 2');

%end
%% clearing all variables from workspace
%clear all ;
