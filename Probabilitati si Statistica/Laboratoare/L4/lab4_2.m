K = 10;
Prob = 0.5;
LocCurent = 0;
vector = repmat(0,1,K);

for i = 1:K
  
  X = rand
  if X < Prob
    LocCurent = LocCurent + 1;
  else
    LocCurent = LocCurent - 1;
  end
  
  vector(i) = LocCurent
    
endfor
