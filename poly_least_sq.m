%function that computes least squares regression for polynomial n

%a is a vector where a(1) = a0, a(2) = a1,...
%Syx is the standard error of x
function [a,r2,Syx] = poly_least_sq(x,y,m)
%this function allows us to enter the degree of the equation of fit -
%should not be used for large m though (ineffective)

n = length(x); %needed?
b = zeros(m+1,1); %might need to transpose
A = zeros(m+1,m+1);

%fills matrices to create system of equations to solve for
for i = 1:m+1
    b(i) = sum(x.^(i-1)*y');
    for j = 1:m+1
            A(i,j) = sum(x.^(i+j -2));
    end
end

%use built in solver; could use Gaussian Elimination, LUDecomp, ect
a = A\b;

%computes Syx, which is the standard error
%Sr = sum(y - sum(a);
%couldn't figure out how to vectorize, so used a loop instead lol
Sr = 0;
for i = 1:n
    x1 = x(i);
    Sr = Sr + (y(i) - sum(a.*(x1.^(0:m))'))^2;
end
Syx = sqrt(Sr/(n - m + 1));
sum_y = sum(y);
mean_y = sum_y/n;
St = sum((y - mean_y).^2);
r2 = 1 - (Sr/St);

end