N = 100;                              # numarul de noduri, N != 0
P = 0.5;                              # probabilitatea
Simulari = 100;                       # numarul de simulari pe care le facem
Pozitie = 0;                          # pozitia curenta pe care ne aflam
deplasari = repmat(0, 1, Simulari);   # vector in care retinem ultima pozitie de la fiecare simulare

for i = 1 : Simulari
  for j = 1 : N
    Random = rand;
    if Random < P
      Pozitie++;
      if(Pozitie == N)  # pentru ca e circular, daca ajung la N resetez la 0
        Pozitie = 0;
      endif
    else
      if(Pozitie == 0)  # inainte sa fac scaderea, verific daca am ajuns la 0
        Pozitie = N;    # pentru ca sigur stim ca mergem un pas in spate, insa
      endif             # acel pas e N - 1, nu -1
      Pozitie--;
    endif    
  endfor
  deplasari(i) = Pozitie
endfor

H = histc(deplasari, 1 : N)
bar(1 : N, H / Simulari, 'hist', 'FaceColor', 'r');