#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



int main(){
char* cislo =(char*)calloc(100000, sizeof(char));

long long int result = 10;
scanf("%s",cislo);
while(result > 9){
result = 0;
long long int k = strlen(cislo);  
for(int i = 0; i < k; i++){
result = result + (int)(cislo[i]) - 48;
cislo[i] = 0;
}

long long int length = snprintf( NULL, 0, "%lld", result );
snprintf(cislo, length + 1, "%lld", result );
}

free(cislo);
printf("%lld\n",result);
return 0;
}

