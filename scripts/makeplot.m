#!/bin/octave -q
#printf("%s\n", argv(){1});
x = [1:10];
plot(x,x.^2,x,x.^2 + x,x,x.^2 - x);
print('asdf.png');
