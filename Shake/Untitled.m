clc ;
clear all;

Data1 = load('data1.txt');
t = Data1(:,1);
x = Data1(:,2);
y = Data1(:,3);

plot3(t,x, y,'r-*');

grid on
hold on