#!/bin/octave -q
#printf("%s\n", argv(){1});
#print('asdf.png');

datafile = argv(){1};
plotfile = argv(){2};

data = csvread( datafile);

G = data(:,1);
data = data(:,2:end);
f = 0:( size( data, 2) - 1);

[f_grid, G_grid] = meshgrid(f,G);

surf( f_grid, G_grid, data);
xlabel("Fitness");
ylabel("Generation");
zlabel("Count");

print( plotfile);