N = -1;
n = 1000;
arr = [];
for i = 1: n
  b1 = b2 = b3 = b4 = b5 = b6 = 0;
  rng = rand();
  if rng >= 0.2
    b1 = 1;
  endif
  rng = rand();
  if (b1 == 1 && rng >= 0.1) || (b1 == 0 && rng >= 0.4)
    b2 = 1;
  endif
  rng = rand();
  if (b1 == 1 && b2 == 1 && rng >= 0.4) || (b2 == 1 && b1 == 0) || (b2 == 0 && b1 == 0 && rng >= 0.1) || (b2 == 0 && b1 == 0 && rng >= 0.6)
    b3 = 1;
  endif
  rng = rand();
  if (b3 == 1 && rng >= 0.7) || (b3 == 0 && rng >= 0.5)
    b4 = 1;
  endif
  rng = rand();
  if (b3 == 1 && rng >= 0.5) || (b3 == 0 && rng >= 0.2)
    b5 = 1;
  endif
  rng = rand();
  if (b5 == 1 && b4 == 1 && rng >= 0.5) || (b5 == 1 && b4 == 0 && rng >= 0.7) || (b5 == 0 && b4 == 1 && rng >= 0.2) || (b5 == 0 && b4 ==0 && rng >= 0.5)
    b6 = 1;
  endif
  N = b1 + b2 * 2 + b3 * 4 + b4 * 8 + b5 * 16 + b6 * 32;
  arr = [arr, N];
endfor
disp(arr);
N=histc(arr,0:64);
p = N(24) / n;
bar(0:64,N/n, 'hist' , 'FaceColor' , 'b' );