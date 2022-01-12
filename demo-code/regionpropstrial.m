clc;
clear all;
close all;

IL =  imread('fire.jpg');
I = rgb2gray(IL);
figure;
imshow(I);
title('GRAYSCALE FLAME IMAGE');
ILE= im2bw(I);
   rmat=IL(:,:,1);              % getting red pixel 
   gmat=IL(:,:,2);             % getting blue pixel
   bmat=IL(:,:,3);            % getting green pixel
 
%% setting level for rgb pixels
levelr= 0.99;
levelg = 0.98;
levelb = 0.97;
i1=im2bw(rmat,levelr);
i2=im2bw(gmat,levelg);
i3=im2bw(bmat,levelb);
Isum = (i1&i2&i3);
%% 
% filling black holes
Ifilled = imfill(Isum,'holes');
se = strel('disk',5);
Iopened = imopen (Ifilled,se);
figure;
imshow(Iopened);
title('FINAL BINARY IMAGE OF FLAME');


%% 
s = regionprops(Iopened, I, {'Centroid','WeightedCentroid'});
figure;
imshow(I);
title('Weighted (red) and Unweighted (blue) Centroid Locations');
hold on
 numObj = numel(s);
for k = 1 : numObj
    plot(s(k).WeightedCentroid(1), s(k).WeightedCentroid(2), 'r*');
    plot(s(k).Centroid(1), s(k).Centroid(2), 'bo');
end
hold off


%% 
s = regionprops(Iopened, I, {'Centroid','PixelValues','BoundingBox'});
imshow(I);
title('Standard Deviation of Regions');
hold on
for k = 1 : numObj
    s(k).StandardDeviation = std(double(s(k).PixelValues));
    text(s(k).Centroid(1),s(k).Centroid(2), ...
        sprintf('%2.1f', s(k).StandardDeviation), ...
        'EdgeColor','b','Color','r');
end
vb = s(k).StandardDeviation;
hold off