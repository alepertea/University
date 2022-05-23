p = 0.5;
k = 10;
n = 1000;
final = [];
rights = [];

for j = 0: n
  poz = 0;
  steps = [];
  done = false;
  right = 0;
  for i = 0: k
    rng = rand();
    if rng >= 1 - p
      poz++;
      steps = [steps, poz];
      if done == false
        right++;
      endif
    else
      poz--;
      done = true;
      steps = [steps, poz];
    endif
  endfor
  final = [final, poz];
  rights = [rights, right];
endfor

N=histc(final,-k:k);
averageRight = mean(rights);
bar(-k:k, N/n, 'hist', 'FaceColor', 'b' );