# g1 : [-2, 2] -> R, g1(x) = e^[-(x^2)]

N = 1000;
a = -2;
b = 2;
M = 2;

f = @(x) exp(-x.^2);

rectangle("Position", [a, 0, (b - a), M]);
title("Function");

hold on;

x = unifrnd(a, b, 1, N);
y = unifrnd(0, M, 1, N);
for i = 1 : N
  px = x(i);
  py = y(i);
  plot(px, py, "*r");
endfor

plot(x, f(x), '*b');

# g3 : [-1, 2] -> [0, INF), g3(x) = x^2 / (1 + x^2), daca x apartine [-1, 0]
#                                   radical(2x - x^2), daca x apartine (0, 2].
a3 = 0; b3 = 2;
g3 = @(x) x.^2./(1 + x.^2).*(x <=0 ) + sqrt(2*x - x.^2).*(x > 0);
t3 = linspace(a3, b3, 1000);
M3 = max(g3(t3))
x3 = unifrnd(a3, b3, 1, n); y3 = unifrnd(0, M3, 1, n);
int3_MC1 = mean(y3 <= g3(x3)) * (b3 - a3) * M3
int3_MC2 = (b3 - a3) * mean(g3(x3))
int3_exact = integral(g3, a3, b3)

