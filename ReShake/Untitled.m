clc ;
clear all;

% Data1 = load('data1.txt');
% t = Data1(:,1);
% x = Data1(:,2);
% y = Data1(:,3);
% 
% plot3(t,x, y,'r-*');
% grid on
% hold on

Data2 = load('data2.txt');
t2 = Data2(:,1);
x2 = Data2(:,2);
y2 = Data2(:,3);
% y3= zeros(length(y2));
% y3([1,20],1)=y2([1,20],1);
% y3([21,:],1)=y2([21,:],1)-10;

plot3(t2,x2, y2,'r-*');

grid on
hold on