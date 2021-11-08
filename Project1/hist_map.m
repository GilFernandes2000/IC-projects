A = fopen('audioHST.txt', 'rt');
C = textscan(A,'%f - %f');

yr = cell2mat(C);

plot(yr(:,1:1), yr(:,2:2));
