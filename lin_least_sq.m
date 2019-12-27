%function that computes linear least sqaures regression 

function [a0,a1,r2] = lin_least_sq(x,y)
%partial derivatives with respect to a0 and a1 are known/always the same
%setting derivates equal to 0 yields a minimum Sr; solving this system of
%equations yields the line of best fit

n = length(x);

%components used in equations solving for a1
sum_x = sum(x);
sum_y = sum(y);
sum_xy = x*y'; %dot product of x and y
sum_x2 = sum(x.^2);

a1 = (n*sum_xy - sum_x*sum_y)/(n*sum_x2 - sum_x^2);

%components used in equations for solving for a0
mean_y = sum_y/n;
mean_x = sum_x/n;

a0 = mean_y - a1*mean_x;

%computing r^2
St = sum((y - mean_y).^2); %Variance of y
Sr = sum((y - a0 - a1*x).^2); %sum of squares

r2 = 1 - Sr/St;

end