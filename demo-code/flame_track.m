
cam=webcam(1);
set(cam, 'Resolution', '320x240');
%for idx = 1:100
 
   I = snapshot(cam);
    IL= rgb2gray(I);
   rmat=I(:,:,1);
   gmat=I(:,:,2);
   bmat=I(:,:,3);

subplot(2,2,1),imshow(rmat);
title('red plane');
subplot(2,2,2),imshow(gmat);
title('green plane');

subplot(2,2,3),imshow(bmat);
title('blue  plane');

subplot(2,2,4),imshow(I);
title('original plane');

levelr= 0.88;
levelg = 0.88;
levelb = 0.88;
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

se = strel('disk',5);
Iopened =imopen(Ifilled,se);
imshow(Iopened);



Iregion = regionprops(Iopened,'centroid');
[labeled,numObjects] =bwlabel(Iopened,4);
stats= regionprops(labeled,'Eccentricity','Area','BoundingBox');
areas=[stats.Area];
eccentricities=[stats.Eccentricity];

idxofflame = find(eccentricities);
statsdefects = stats(idxofflame);
figure,imshow(I);
hold on;
for idx = 1: length(idxofflame)
       h= rectangle('Position',statsdefects(idx).BoundingBox);
       set(h,'EdgeColor',[.75 0 0]);
       
       hold on;
end
%end