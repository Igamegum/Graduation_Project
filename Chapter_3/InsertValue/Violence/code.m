clc ;
clear all;

Data1 = load('insert/nodata.txt');
%x = Data1(:,1);
y = Data1(:,2);
z = Data1(:,3);
plot( y, z+2,'r-*');

grid on
hold on


Data2 = load('insert/double.txt');
%x = Data1(:,1);
y = Data2(:,2);
z = Data2(:,3);
plot( y, z,'g-*');

grid on
hold on




