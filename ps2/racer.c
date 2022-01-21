#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct speed {
 int s;
 int v;
};


int main(){

int n, t;
scanf("%d %d ",&n,&t);
struct speed list[n];

long double min = 10000000000;

for(int i = 0; i < n; i++){
  scanf("%d %d", &list[i].s, &list[i].v);
  min = (list[i].v > min) ? min : list[i].v; 
  char ch;
  scanf("%c",&ch);
}


long double a = -min + 0.0000000001;
long double b = 1000000;
long double  x = 0;
long double  y = -t;

while(b - a > 0.0000000001 ){
 y = 0;
  x = (a+b)/2;
  
  for(int i = 0; i < n; i++){
  
    y =y + list[i].s/(x+list[i].v);
 
   }

  if(y < t){
   b = x;
  }
  else if (y > t){
   a = x;
  }
 }
printf("%.9Lf\n",x);
return 0;
}
