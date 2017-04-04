clc ;
clear all;

Data1 = load('data8.txt');
x = Data1(:,1);
y = Data1(:,2);
plot(x, y,'r-*');

grid on
hold on


Data2 = load('miss358.txt');
x2 = Data2(:,1);
y2 = Data2(:,2);
plot(x2, y2,'b-*');

grid on
hold on
