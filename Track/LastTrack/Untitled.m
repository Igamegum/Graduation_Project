clc ;
clear all;

Data1 = load('perfect.txt');
x = Data1(:,1);
y = Data1(:,2);

plot(x, y,'r-*');

grid on
hold on



Data2 = load('chaos.txt');
x2 = Data2(:,1);
y2 = Data2(:,2);

plot(x2, y2+10,'b-*');

grid on
hold on