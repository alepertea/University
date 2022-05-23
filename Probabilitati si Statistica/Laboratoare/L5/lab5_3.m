N = 1000;
nrAruncari = 0;
vecx = [];
vecy = [];

for i = 1 : N
  u1 = rand;
  u2 = rand;
  
  x = sqrt(-2 * log(u1)) * cos(2 * 3.14 * u2)
  y = sqrt(-2 * log(u1)) * sin(2 * 3.14 * u2)
  
  if x * x + y * y <= 0.25
    nrAruncari = nrAruncari + 1
    vecx = [vecx, x];
    vecy = [vecy, y];
  endif
  
endfor

disp(nrAruncari / N)