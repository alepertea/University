Simulari = 1000;    # numarul de simulari
aruncari = 0;       # numarul de aruncari
vector = [];        # vector in care retinem toate seturile de aruncari pana la succes
P1 = 0.5; P2 = 0.3; # P1 - prob pt prima moneda; P2 - prob pt a doua moneda

for i = 1 : Simulari
  M1 = rand; M2 = rand;
  if M1 <= P1 && M2 <= P2
      vector = [vector, aruncari];  # adaugam in vector aruncarile
      aruncari = 0;                 # resetam numarul de aruncari
  else
      aruncari++;
  endif
endfor

Media = mean(vector)  # fac media seturilor de aruncari