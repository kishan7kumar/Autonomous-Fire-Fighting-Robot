clc;
clear all;
close all;
cam=webcam(2);   % accessing web camera to start detecting  flame
delete(instrfindall);                 %set(cam, 'Resolution', '320x240');   %setting camera resolution
s = serial('COM4','BaudRate',9600);
fopen(s);

for idx = 1:100                   % loop function for live feed for 1m 30secs
   
   I = snapshot(cam);          %getting one frame from camera
   IL= rgb2gray(I);           % converting that frame to gray scale image
   rmat=I(:,:,1);             % getting red pixel 
   gmat=I(:,:,2);             % getting blue pixel
   bmat=I(:,:,3);            % getting green pixel
 
%% setting level for rgb pixels
% levelr= 0.99;
% levelg = 0.99;
% levelb = 0.99;
% i1=im2bw(rmat,levelr);
% i2=im2bw(gmat,levelg);
% i3=im2bw(bmat,levelb);
Isum = rmat>250  & bmat>250 & gmat>250 ;  %(i1-i2)&(i3-i2-i1); %(i1&i2&i3);
% figure;
% imshow(Isum);
%% 
% filling black holes
Ifilled = imfill(Isum,'holes');
se = strel('disk',5);

Iopened = imopen (Ifilled,se);

%Iregion = regionprops(Iopened,'Centroid');
[labeled,numObjects] = bwlabel(Iopened,4);
stats= regionprops(labeled,'Eccentricity','Area','BoundingBox');  %,'PixelValues'

areas=[stats.Area];
eccentricities=[stats.Eccentricity];
myarea = areas < 200 & areas > 1 ;
areafinal = stats(myarea);
%pixelvalues = [stats.PixelValues];
idxofflame = find(eccentricities);
statsdefects = stats(idxofflame);
imshow(I);
hold on;
  if isempty(areafinal)
     %disp('no fire');
    % 
  else
      fwrite(s,'F'); 
      pause(1);
     fwrite(s,'N');
   for idx = 1: length(areafinal)
       h= rectangle('Position',statsdefects(idx).BoundingBox); 
       set(h,'EdgeColor',[0 0 1],'LineWidth',2);
       hold on;
   end   
  end 
end
fclose(s);

%delete(instrfindall);      
