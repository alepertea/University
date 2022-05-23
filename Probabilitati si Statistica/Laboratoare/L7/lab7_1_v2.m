x = [12, 3, 5, 20, 50, 12, 45, 60, 32, 57, 86, 12]; % vectorul de date statistice
alfa = 0.1; % nivelul de semnificatie
n = length(x); % lungimea vectorului
media = mean(x); % media vectorului x

%i)
cuantila = norminv(1 - alfa / 2, 0, 1); % cuantila legii normale N(0,1)
s = 2; % sigma
  
stanga = media - s / sqrt(n) * cuantila;
dreapta = media + s / sqrt(n) * cuantila;

rezultat = [stanga, dreapta]

%ii)
cuantila = tinv(1 - alfa / 2, n - 1);
sn = std(x);
   
stanga = media - sn / sqrt(n) * cuantila;
dreapta = media + sn / sqrt(n) * cuantila;
   
rezultat = [stanga, dreapta]

%iii)
c1 = chi2inv(1 - a / 2, n - 1);
c2 = chi2inv(a / 2, n - 1);

stanga = sqrt(( n - 1) / c1) * sn;
dreapta = sqrt((n - 1 ) / c2) * sn;

rezultat = [stanga, dreapta]

%iv)
xBool = [0, 0, 1, 1, 1, 1, 0, 0, 1, 0];
n = length(xBool);
media = mean(xBool);

stanga = media - sqrt(media * (1 - media) / n) * norminv(1 - a / 2, 0, 1);
dreapta = media + sqrt(media * (1 - media) / n) * norminv(1 - a / 2, 0, 1);

rezFinal = [];
for i = stanga + 1 : dreapta - 1
  
  if i > 0 && i < 1
    rezFinal = [rezFinal, i];
  endif
  
endfor

rezultat = rezFinal
