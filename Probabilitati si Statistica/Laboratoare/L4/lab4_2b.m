M = 10;
K = 10;
P = 0.5;
LocCurent = 0;
vector = repmat(0,1,K);

for i = 1 : M
  
  for j = 1 : K
    X = rand;
    if X < P
      LocCurent = LocCurent + 1;
    else
      LocCurent = LocCurent - 1;
    end
  endfor
  
  vector(i) = LocCurent
endfor

N = histc(vector, -K : K)
bar(-K : K, N / 1000, 'hist', 'FaceColor', 'r');