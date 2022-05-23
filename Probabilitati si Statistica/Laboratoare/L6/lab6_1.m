N = 500;
valMedie = 165;
deviatia = 10;

# i)
vector = normrnd(valMedie, deviatia, 1, N);
hist(vector, 10)

# iii)
vectorInaltimi = [];
for i = 1 : N
  # retin intr-un vector inaltimile generate din intervalul [160, 170]
  if vector(i) >= 160 && vector(i) <= 170
    vectorInaltimi = [vectorInaltimi, vector(i)];
  endif
endfor

ValoareaMedie = mean(vector)
valMedie

DeviatiaStandard = std(vector)
deviatia

frecventaRelativa = length(vectorInaltimi) / N
frecventaTeoretica = normcdf(170, valMedie, deviatia) - normcdf(160, valMedie, deviatia)