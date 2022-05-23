N = 5000;
r = 5;
v = 2;
a = 3;

vr = [repmat("r", 1, r)];
vv = [repmat("v", 1, r)];
va = [repmat("a", 1, r)];

vfinal = [vr, vv, va];

nrCazuri = 0;

for i=1:N
  a = randsample(vfinal, 3);
  if(a(1,:) == "rrr")
    nrCazuri++;
  endif
endfor

disp(nrCazuri)
disp(nrCazuri/N)
