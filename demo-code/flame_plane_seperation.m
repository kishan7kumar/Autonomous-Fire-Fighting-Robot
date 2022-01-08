clc;
close all;
clear all;
I = imread('flamenew.jpg');
%cam=webcam(2);
%I = snapshot(cam);
IL= rgb2gray(I);
rmat=I(:,:,1);
gmat=I(:,:,2);
bmat=I(:,:,3);

% title('red plane');
% subplot(2,2,2),imshow(gmat);
% title('green plane');
% 
% subplot(2,2,3),imshow(bmat);
% title('blue  plane');
% 
% subplot(2,2,4),imshow(I);
% title('original plane');

levelr= 0.59;
levelg = 0.99;
levelb = 0.59;
i1=im2bw(rmat,levelr);
i2=im2bw(gmat,levelg);
i3=im2bw(bmat,levelb);
Isum = (i1&i2&i3);

subplot(2,2,1),imshow(i1);
title('red plane');
subplot(2,2,2),imshow(i2);
title('green plane');
subplot(2,2,3),imshow(i3);
title('blue  plane');
subplot(2,2,4),imshow(Isum);
title('sum of all plane');
% filling blacnk holes
Ifilled = imfill(Isum,'holes');
figure, imshow(Ifilled);
se = strel('diamond',5);
Iopened = imopen(Ifilled,se);
imshow(Iopened);

%Iregion = regionprops(Isum,'Centroid');
[labeled,numObjects] = bwlabel(Iopened,4);
stats= regionprops(labeled,'Eccentricity','Area','MajorAxisLength','BoundingBox');  
areas=[stats.Area];
eccentricities=[stats.Eccentricity];
lengths=[stats.MajorAxisLength];
eidx = lengths < 20;
imageStatsFinal = stats(eidx);
 idxofflame = find(eccentricities);
statsdefects = stats(idxofflame);
figure,imshow(I);
hold on;
if isempty(imageStatsFinal)
    
for idx = 1: length(idxofflame)
       h= rectangle('Position',statsdefects(idx).BoundingBox);
       set(h,'EdgeColor',[0 0 1]);
       
       hold on;
end   
end
