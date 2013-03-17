#!/bin/octave -q
#printf("%s\n", argv(){1});
#print('asdf.png');

datafile = argv(){1};
plotfile = argv(){2};

data = csvread( datafile);

G = data(:,1);
nSols = data(:,2);
data = data(:,3:end);
f = 0:( size( data, 2) - 1);

[f_grid, G_grid] = meshgrid(f,G);

contourf( f_grid, G_grid, data);
xlabel("Fitness");
ylabel("Generation");
zlabel("Count");
print( strcat(plotfile,"_quality.png"));

plot( G, nSols);
xlabel("Generation");
ylabel("Number of Solutions found");
print( strcat(plotfile,"_nSolutions.png"));