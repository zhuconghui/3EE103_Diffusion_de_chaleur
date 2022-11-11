a=load("Diffusion.txt");
% b=load("Diffusion 2.txt");
[m,n]=size(a);

figure(1);
imagesc(a);
colorbar;
title("Diffusion de la chaleur bidimensionnel(RK2) au bout de 100s");

% figure(2);
% imagesc(b);
% colorbar;
% title("Diffusion de la chaleur monodimensionnel au bout de 1000s");