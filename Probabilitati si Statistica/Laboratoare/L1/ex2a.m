n=input('Introduceti n=');
k=input('Introduceti k=');

disp('Matricea posibilelor asezari a elementelor 0 in cadrul sirurilor binare:')
P=nchoosek(1:n+k-1,k-1)  %matricea pozitiilor lui 0

disp('Matricea sirurilor binare:')
T=ones(nchoosek(n+k-1,k-1),n+k-1);% cream matricea cu sirurile binare
for j=1:nchoosek(n+k-1,k-1)
  T(j,P(j,:))=0;   %pe fiecare linie j avem o alta aranjare a elementelor conform 
end                %poziitiilor lui 0 din matricea P
T   %afisam T

M=zeros(nchoosek(n+k-1,k-1),k); %initializam maticea principala cu solutiile

for j=1:nchoosek(n+k-1,k-1) %parcurgem numarul de linii din matricea P
  i=1;  %pe linia j incepem cu indicele i=1 corespunzator primei coloane in M
  for a=1:n+k-1  %parcurgem toate pozitiile din sirul nostru binar de pe linia j din T
    if T(j,a)==1   %daca pe pozitia a este un element egal cu 1
      M(j,i)=M(j,i)+1;   %adaugam 1 la elementul de pe linia j coloana i din M
    else
      i=i+1;   %altfel trecem mai departe la urmatorul element al liniei j din M 
    end
  end
end


fprintf('Cele %d solutii ale ecuatiei sunt:\n',nchoosek(n+k-1,k-1)) %f in loc de d pentru numere fractionare
M   %afisam M
  
