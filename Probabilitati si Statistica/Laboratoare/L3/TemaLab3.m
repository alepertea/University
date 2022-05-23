pkg load statistics;

N = 5000;   # numarul de simulari
P = 2/6;    # probabilitatea ca, daca arunci un zar, sa arate un numar divizibil cu 3
Cazuri = 0; # numarul de cazuri in care 2 din 5 zaruri vor da un numar divizibil cu 3

for i = 1 : N
  X = binornd(5, P);
  if X == 2
    Cazuri = Cazuri + 1;
  endif
endfor

Probabilitate = Cazuri / N
binopdf(2, 5, P)