#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.1415926535

struct diery {
//string[20000];
long double R;
long double X;
long double Y;
long double Z;
};

int main(){

int M, S;
scanf("%d %d",&M,&S);
char ch = 0;
scanf("%c",&ch);

struct diery list[M];

if(M == 0){
 for(int i = 0; i < S; i++){
   printf("%.9Le\n",(long double)(100/S));
 }
 return 0;
}

if(S==1){
 printf("100.000000\n");
 return 0;
}

for(int i = 0; i < M; i++){
 scanf("%Le %Le %Le %Le",&list[i].R,&list[i].X,&list[i].Y,&list[i].Z);
  ch = 0;
  scanf("%c",&ch);
}

long double obv = pow(10,15);

for(int i = 0; i < M; i++){
  obv = obv - (long double)(4*PI*pow(list[i].R,3))/(long double)3;
}

long double obv_kus = (long double)obv/S;
long double len_kus_or = 100000/S;
long double vsetky_kusy =  0;

for(int j = 0; j < S; j++){
len_kus_or = 100000/S;
vsetky_kusy += len_kus_or;
long double obv_kus_or = len_kus_or*10000000000;

int ind = 6; 
while(ind != -6){
   long double obv_dier_kus = 0;
   for(int i = 0; i < M; i++){
   long double H = 0;
   if((list[i].Z-list[i].R) < (vsetky_kusy - len_kus_or)&& (list[i].Z+list[i].R) > (vsetky_kusy - len_kus_or) && vsetky_kusy > (list[i].Z+list[i].R)){

       H = list[i].Z + list[i].R-(vsetky_kusy - len_kus_or);
       obv_dier_kus +=  PI*H*H*(list[i].R - (long double)(H/3));

   }
   if((list[i].Z-list[i].R) > (vsetky_kusy - len_kus_or) && vsetky_kusy < (list[i].Z+list[i].R) && (list[i].Z-list[i].R) < vsetky_kusy){
     
       H = vsetky_kusy - (list[i].Z - list[i].R);
       obv_dier_kus +=  PI*H*H*(list[i].R - (long double)(H/3));

   }
    if((list[i].Z-list[i].R) < (vsetky_kusy - len_kus_or) && vsetky_kusy < (list[i].Z+list[i].R)){
    long double h1 = vsetky_kusy - len_kus_or - (list[i].Z-list[i].R);
    long double h2 = (list[i].Z+list[i].R) - vsetky_kusy;
     
     obv_dier_kus +=(long double)(4*PI*pow(list[i].R,3)/3) -  PI*h1*h1*(list[i].R - (long double)(h1/3)) - PI*h2*h2*(list[i].R - (long double)(h2/3));
      
   }

   if((list[i].Z-list[i].R) > (vsetky_kusy - len_kus_or) && vsetky_kusy > (list[i].Z+list[i].R)){

     obv_dier_kus +=(long double)((4*PI*pow(list[i].R,3))/3);
   }
  }
   obv_kus_or = len_kus_or * pow(10,10) - obv_dier_kus;
  
  if(roundf(obv_kus_or/pow(10,ind+10)) == roundf(obv_kus/pow(10,ind+10))){
      ind--;   
  } 
   len_kus_or = (roundf(obv_kus_or/pow(10,ind+10)) <  roundf(obv_kus/pow(10,ind+10))) ? (len_kus_or + pow(10,ind)) : (len_kus_or - pow(10,ind));
   vsetky_kusy = (roundf(obv_kus_or/pow(10,ind+10)) <  roundf(obv_kus/pow(10,ind+10))) ? (vsetky_kusy + pow(10,ind)) : (vsetky_kusy - pow(10,ind));
  
  //printf("%f %f\n",roundf((obv_kus_or/pow(10,10))/pow(10,ind)),roundf((obv_kus/pow(10,10))/pow(10,ind)));
 }
 printf("%.9f\n",(float)len_kus_or/1000);
 }
return 0;
}

