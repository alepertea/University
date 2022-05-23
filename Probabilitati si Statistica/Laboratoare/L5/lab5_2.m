N = 100;
Lambda = 1/12;
vec = [];
S = 0;

for i = 1 : N
  r = rand;
  x = -1 / Lambda * log(1 - r);
  S = S + x;
  vec = [vec, x];
endfor

Media = mean(vec)
Deviatia = std(vec)