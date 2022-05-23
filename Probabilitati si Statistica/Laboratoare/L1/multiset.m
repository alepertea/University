function A=multiset(S,n)
k=length(S);
P=soleq(n,k)
A=zeros(nchoosek(n+k-1,k-1),n);
for j=1:nchoosek(n+k-1,k-1)
  M=[];
  for i=1:k
    M=[M,S(i)*ones(1,P(j,i))];
  end
  A(j,:)=M;
end
end