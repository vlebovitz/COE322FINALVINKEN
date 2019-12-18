data = load('lengthOfDisease.txt');

x = data(:,1);
y = data(:,2);

plot(x,y);
xlabel('Vaccination');
ylabel("Length of Disease(days)");
title('Vaccination vs Length Of Disease')
