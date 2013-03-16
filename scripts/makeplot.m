#!/bin/octave -q
#printf("%s\n", argv(){1});
#print('asdf.png');

datafile = argv(){1};
plotfile = argv(){2};
data = csvread( datafile);
surf( data);
xlabel("X Label");
ylabel("Y Label");
zlabel("Z Label");
print( plotfile);