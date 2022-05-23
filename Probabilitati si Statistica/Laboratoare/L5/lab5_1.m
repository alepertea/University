N = 1000;
i1 = 0.46; i2 = 0.86; i3 = 0.96; i4 = 1;
vec = [];

for i = 1 : N
  r = rand;
  interval = 0;
  
  if r <= i1
    interval = 1;
  endif
  
  if r >= i1 && r <= i2
    interval = 2;
  endif
  
  if r > i2 && r <= i3
    interval = 3;
  endif
  
  if r > i3
    interval = 4;
  endif
  
  vec = [vec, interval];
endfor

nr1 = length(find(vec == 1)) / N;
nr2 = length(find(vec == 2)) / N;
nr3 = length(find(vec == 3)) / N;
nr4 = length(find(vec == 4)) / N;

histograma = histc(vec, 1 : 4);
bar(1 : 4, histograma / N, "hist");