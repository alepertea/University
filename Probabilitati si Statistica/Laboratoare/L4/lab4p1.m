NR=1000;

vec=[repmat(0,1,64)];

for i=1:NR
  
  X=rand(1,6);
  r=[0,0,0,0,0,0];
  r(1)=binornd(1,0.8,1,1);
  
  
 P=1;

  if r(1) == 0
     P=0.9;
   else
     p=0.6;
    end
  r(2)=binornd(1,P,1,1);
  
  if r(2)==1 && r(1)==1
    P=0.6;
   
 end
 
   if r(2)==1 && r(1)==0
    P=0.2;
   
  end
 
  if r(2)==0 && r(1)==1
    P=0.9;
   
 end
 
   if r(2)==0 && r(1)==0
    P=0.4;
   
 end
    
   r(3)=binornd(1,P,1,1);
   
   if r(3)==1
     P=0.3;
    else
     P=0.5;
   end
   
   r(4)=binornd(1,P,1,1);
   
   if r(3)==1
     P=0.5;
    else
     P=0.8;
   end
   
   r(5)=binornd(1,P,1,1);
   
   if r(5)==1 && r(4)==1
    P=0.5;
   
 end
 
   if r(5)==1 && r(4)==0
    P=0.3;
   
  end
 
  if r(5)==0 && r(4)==1
    P=0.8;
   
 end
 
   if r(5)==0 && r(4)==0
    P=0.5;
   
 end
 
 r(6)=binornd(1,P,1,1);
 
 disp(r);
 r=num2str(r);
 dec = bin2dec(r)

 vec(dec) = vec(dec)+1;
 
  
endfor

N=histc(vec,0:64);

bar(0:64,N/NR, "hist" , "FaceColor" , "b" );
