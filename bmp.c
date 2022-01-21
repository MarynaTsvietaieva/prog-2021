
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "bmp.h"
#define ALPH "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

char* reverse(const char* text){
if(text == NULL){
        return 0;
}
char *r = calloc(strlen(text)+1, sizeof(*text));
size_t l = strlen(text);

   for(int i = l - 1; i >= 0; i--) {
        r[l-i-1] = text[i];
        if(text[i] > 96 && text[i] < 123){
         r[l-i-1] = r[l-i-1]-32;
        }
    }

     r[l] = '\0';

    return r;
}

char* vigenere_encrypt(const char* key, const char* text){
 if(text == NULL){
      return 0;
    }
 if(key == NULL){
   return 0;
  }
 for(int i=0; i < strlen(key); i++){
    if(key[i] < 'A' ||(key[i]>'Z' && key[i] < 'a') || key[i] >'z'){
      return 0;
      break;
    }
 }
char* key2 = calloc(strlen(text)+1, sizeof(*text));
char* str1 = calloc(strlen(text)+1, sizeof(*text));
char* str2 = calloc(strlen(text)+1, sizeof(*text));
char* new_str =  calloc(strlen(text)+1, sizeof(*text));
char* result =  calloc(strlen(text)+1, sizeof(*text));
int idx = 0;

for(int i = 0; i < strlen(text);i++){

     if((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')){
         key2[i] = key[idx%strlen(key)];
         idx++;
       }
     else{
        key2[i] = text[i];
     }                  
          if(text[i] >= 'A' && text[i] <='Z'){
             str1[i] = text[i]-'A';
          }
          else if(text[i] >= 'a' && text[i] <= 'z'){
            str1[i] = text[i]-'a';
           }
          else{
            str1[i] = text[i];
           }
          
          if(key2[i] >= 'A' && key2[i] <='Z'){
             str2[i] = key2[i]-'A';
          }
          else if(key2[i] >= 'a' && key2[i] <= 'z'){
            str2[i] = key2[i]-'a';
           }
          else{
            str2[i] = key2[i];
           }

          new_str[i] = (str1[i] >=0 && str1[i]<27) ? (int)((str1[i]+str2[i])%26) : (int)(str1[i]);
          result[i] = ((int)(new_str[i]) < 26) ? ALPH[(int)(new_str[i])] : new_str[i] ;
    }
free(key2);
free(str1);
free(str2);
free(new_str);
return result;

free(result);
}

char* vigenere_decrypt(const char* key, const char* text){
 if(text == NULL){
      return 0;
    }
 if(key == NULL){
   return 0;
  }
 for(int i=0; i < strlen(key); i++){
    if(key[i] < 'A' ||(key[i]>'Z' && key[i] < 'a') || key[i] >'z'){
      return 0;
      break;
    }
 }
  char* key2 = calloc(strlen(text)+1, sizeof(*text));
  char* str1 = calloc(strlen(text)+1, sizeof(*text));
  char* str2 = calloc(strlen(text)+1, sizeof(*text));
  char* new_str =  calloc(strlen(text)+1, sizeof(*text));
  char* result =  calloc(strlen(text)+1, sizeof(*text));
  int idx = 0;
  for(int i = 0; i < strlen(text);i++){
    
     if((text[i] >='A' && text[i] <= 'Z') || (text[i] >='a' && text[i] <='z')){
         key2[i] = key[idx%strlen(key)];
         idx++;
       }
     else{
        key2[i] = text[i];
     }
          if(text[i] >= 'A' && text[i] <='Z'){
             str1[i] = text[i]-'A';
          }
          else if(text[i] >='a' && text[i] <='z'){
            str1[i] = text[i]-'a';
           }
          else{
            str1[i] = text[i];
           }
        
          if(key2[i] >= 'A' && key2[i] <='Z'){
             str2[i] = key2[i]-'A';
          }
          else if(key2[i] >='a' && key2[i] <='z'){
            str2[i] = key2[i]-'a';
           }
          else{
            str2[i] = key2[i];
           }

          new_str[i] = (str1[i] >-1 && str1[i]<27) ? (int)((str1[i]-str2[i]+26)%26) : (int)(str1[i]);
          result[i] = ((int)(new_str[i]) < 26) ? ALPH[(int)(new_str[i])] : new_str[i];
    }


free(key2);
free(str1);
free(str2);
free(new_str);
return result;

}

unsigned char* bit_encrypt(const char* text){
if(text == NULL){
    return NULL;
  }
  
  size_t len = strlen(text);
  unsigned char* result = calloc(strlen(text)+1, sizeof(*text));
  unsigned char* one = (unsigned char*)malloc(8 * sizeof(unsigned char));
 for(int index = 0; index < len; index++){
  int c = text[index];
  int i = 7;
  while(c !=1){
   one[i] = ((c%2 == 0) ? false : true);
   i--;
   c = c/2;
   }
   one[i] = true;
   i--;
   for(int p=i; p>-1; p--){
     one[p]=false;
    }
  
  for(int ind=0; ind <3;ind = ind+2){
    one[ind] = one[ind]+one[ind+1]; 
    one[ind+1] = one[ind]-one[ind+1]; 
    one[ind] = one[ind]-one[ind+1];

    one[ind+4] = one[ind]^one[ind+4];
    one[ind+5] = one[ind+1]^one[ind+5];  
}
  
int sum = 0;
   for(int i = 0; i < 8; i++){
       int binary = (one[i]==true) ? 1 : 0;
       sum = sum + binary*pow(2,7-i);
    }
   result[index] = sum;
}
result[strlen(text)] = '\0';

free(one);
return result;
free(result);

}

char* bit_decrypt(const unsigned char* text){
if(text == NULL){
    return NULL;
  }
  int len;
  for(len=0;text[len] != '\0'; len++ ){
     }
  char* result = calloc(len+1, sizeof(*text));
  unsigned char* one = (unsigned char*)malloc(8 * sizeof(unsigned char));
 for(int index = 0; index < len; index++){
  int c = text[index];
  int i = 7;
  while(c !=1){
   one[i] = ((c%2 == 0) ? false : true);
   i--;
   c = c/2;
   }
   one[i] = true;
   i--;
   for(int p=i; p>-1; p--){
     one[p]=false;
    }
  
  for(int ind=0; ind <3;ind = ind+2){
    one[ind+4] = one[ind]^one[ind+4];
    one[ind+5] = one[ind+1]^one[ind+5];

    one[ind] = one[ind]+one[ind+1]; 
    one[ind+1] = one[ind]-one[ind+1]; 
    one[ind] = one[ind]-one[ind+1];

    }
  
int sum = 0;
   for(int i = 0; i < 8; i++){
       int binary = (one[i]==true) ? 1 : 0;
       sum = sum + binary*pow(2,7-i);
    }
   result[index] = sum;
}
result[len] = '\0';

free(one);
return result;
free(result);


}

unsigned char* bmp_encrypt(const char* key, const char* text){
  char* abra = reverse(text);
  char* b = vigenere_encrypt(key,abra);
  unsigned char* c = bit_encrypt(b);

free(abra);
free(b);

return c;
free(c); 
}

char* bmp_decrypt(const char* key, const unsigned char* text){
  char* abra = bit_decrypt(text);
  char* b = vigenere_decrypt(key,abra);
  char* c = reverse(b);

free(abra);
free(b);

return c;
free(c);

}

//int main(){

//char* rev = reverse("gripe");
//printf("%s",rev);
//char* encrypted;//, *decrypted;
// basic test with long text
//encrypted = vigenere_encrypt("", "Hello world!");
//printf("%s\n", encrypted);

//decrypted = vigenere_decrypt("CoMPuTeR", encrypted);
//printf("%s\n", decrypted);
//unsigned char* encrypted;
//encrypted = bit_encrypt("Hello world!");
//for(int i=0; i < 12;i++) {
//    printf("%x ", encrypted[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
//}
//free(encrypted);

//char* dec;
//dec = bit_decrypt({80});
//for(int i=0; i < 12;i++) {
//    printf("%c ", encrypted[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
//}
//free(dec);
//unsigned char* encrypted2;
//xy basic test with long text
//encrypted2 = bit_encrypt("Hello world!");
//for(int i=0; i < 12;i++) {
//    printf("%x ", encrypted2[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
//}

//char* dencrypted2;
//xy basic test with long text
//dencrypted2 = bit_decrypt(encrypted2);
//for(int i=0; i < 12;i++) {
//    printf("%c ", dencrypted2[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
//}

//free(dencrypted2);
//free(encrypted2);

//unsigned char* a;
//a = bmp_encrypt("SeCReT", "Hello world!");
//for(int i=0; i < 12;i++) {
//    printf("%x ", a[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
//}

//char* b;

//b = bmp_decrypt("SeCReT",a);
//for(int i=0; i < 12;i++) {
//    printf("%c ", b[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
//}

//return 0;
//}
