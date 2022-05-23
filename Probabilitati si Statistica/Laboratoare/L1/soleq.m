function M=soleq(n,k)
P=nchoosek(1:n+k-1,k-1);  %matricea cu pozitiile lui 0
M=zeros(nchoosek(n+k-1,k-1),k); %initializam matricea pricipala cu solutii

for j=1:nchoosek(n+k-1,k-1) %parcurgem numarul de liniii din matricea P
  v=ones(1,n+k-1);  % cream vectorul  sirului binar corespunzator liniei j
  v(P(j,:))=0;      % din matricea P 
 
  i=1;  %pe linia j incepem cu indicele i=1 corespunzator primei coloane in M
  for a=1:n+k-1  %parcurgem toate pozitiile din sirul nostru binar de pe linia j
    if v(a)==1    %daca pe pozitia a din sir este un element egal cu 1
      M(j,i)=M(j,i)+1;  %adaugam 1 la elementul de pe linia j coloana i din M
    else
      i=i+1;   %altfel trecem mai departe la urmatorul element al liniei j din M
    end
  end
  
end

 
endfunction
