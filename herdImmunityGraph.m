data = load('HerdImmunity.txt');

x = data(:,2);
y = data(:,1);

plot(x,y);
xlabel('Vaccination Rate to Achieve .95 Immunity');
ylabel("Contagiousness");
title('Herd Immunity Graph')
