#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "playfair.h"
#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVXYZ"

void make_key(const char** key,char**h);
void make_matrix(char** key_edit, char *** matrix);
void make_text(const char** text,char** new_string);
char* playfair_encrypt(const char* key, const char* text);
char* playfair_decrypt(const char* key, const char* text);
char* decripy(char** matrix, const char* text);



char* playfair_encrypt(const char* key, const char* text) {
     int k = 0;
     int k1 = 0;
     int k2 = 0;
     if(key == NULL){
     return 0;
     }
     if(text == NULL){
      return 0;
     }
    for(int i = 0; i < strlen(key);i++){
       if((key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z')){
         k1++;
       }
       if((key[i] < 'A' || (key[i] > 'Z' && key[i] < 'a') || key[i] > 'z') && key[i] != ' '){
        k = 1;
       }
    }
    if(strcmp(text, "") == 0 || strcmp(key,"") == 0){
      k=1;
    } 
    
    for(int i = 0; i < strlen(text);i++){
       if((text[i] < 'A' || (text[i] > 'Z' && text[i] < 'a') || text[i] > 'z') && text[i] != ' '){
        k = 1;
       }
       if((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')){
         k2++;
       }
    }
     if(k != 0 || k1 == 0 || k2==0){
       return 0;
    }
 
    char* h = malloc(strlen(key) * sizeof(*key));
    make_key(&key,&h);
    char** matrix = (char**)malloc(5 * sizeof(char*));
    make_matrix(&h,&matrix);
    char* new_text = (char*)malloc(strlen(text) * sizeof(char));
    make_text(&text,&new_text);
    char* string = malloc((strlen(new_text) * 1.5) * sizeof(*new_text));
      int a, b, a1, b1;
      int number_new = 0;
      for (int number = 0; number < strlen(new_text);number = number + 2) {
          for (int i = 0; i < 5;i++) {
              for (int idx = 0; idx < 5; idx++) {
                  if (new_text[number] == matrix[i][idx]) {
                      a = i;
                      b = idx;
                  }
                  if (new_text[number + 1] == matrix[i][idx]) {
                      a1 = i;
                      b1 = idx;
                  }
              }
          }
          if (a != a1 && b != b1) {
              string[number_new] = matrix[a][b1];
              string[number_new + 1] = matrix[a1][b];
          }
          else if (a == a1 && b != b1) {
              string[number_new] = matrix[a][(b + 1) % 5];
              string[number_new + 1] = matrix[a1][(b1 + 1) % 5];
         }
         else if (b == b1) {
             string[number_new] = matrix[(a + 1) % 5][b];
             string[number_new + 1] = matrix[(a1 + 1) % 5][b1];
         }
         string[number_new + 2] = ' ';
         number_new = number_new + 3;

     }
    string[number_new - 1] = '\0';
    free(h);
    free(new_text);
    free(matrix);
    return string;
    free(string);
}
char* playfair_decrypt(const char* key, const char* text) {
   int k = 0;
   int k1 = 0;
   int k2 = 0;
    if(key == NULL){
      return 0;
    }
    if(text == NULL){
     return 0;
      }
    for(int i = 0; i < strlen(key);i++){
       if((key[i] < 'A' || (key[i] > 'Z' && key[i] < 'a') || key[i] > 'z') && key[i] != ' '){
        k = 1;
       }
     if((key[i] > 'A' && key[i] < 'Z') || (key[i] > 'a' && key[i] < 'z')){
         k1++;
       }
    }
    if(strcmp(text, "") == 0 || strcmp(key,"") == 0){
      k=1;
    }

    for(int i = 0; i < strlen(text);i++){
       if((text[i] < 'A' || (text[i] > 'Z' && text[i] < 'a') || text[i] > 'z' || text[i] == 'W' || text[i] == 'w') && text[i] != ' '){
        k = 1;
       }
       if((text[i] > 'A' && text[i] < 'Z') || (text[i] > 'a' && text[i] < 'z')){
         k2++;
       }
    }
     if(k != 0 || k1==0 ||k2 ==0){
       return 0;
    }

    char* h = malloc(strlen(key) * sizeof(*key));
    make_key(&key,&h);
    char** matrix = (char**)malloc(5 * sizeof(char*));
    make_matrix(&h,&matrix);
    char* string = malloc(strlen(text) * sizeof(text));
    int a, b, a1, b1;
    int number_new = 0;
    for (int number = 0; number < strlen(text);number = number + 3) {
        for (int i = 0; i < 5;i++) {
            for (int idx = 0; idx < 5; idx++) {
                if (text[number] == matrix[i][idx]) {
                    a = i;
                    b = idx;
                }
                if (text[number + 1] == matrix[i][idx]) {
                    a1 = i;
                    b1 = idx;
                }
            }
        }
        if (a != a1 && b != b1) {
            string[number_new] = matrix[a][b1];
            string[number_new + 1] = matrix[a1][b];
        }
        else if (a == a1 && b != b1) {
            string[number_new] = matrix[a][(b + 4) % 5];
            string[number_new + 1] = matrix[a1][(b1 + 4) % 5];
        }
        else if (b == b1) {
            string[number_new] = matrix[(a + 4) % 5][b];
            string[number_new + 1] = matrix[(a1 + 4) % 5][b1];
        }
        number_new = number_new + 2;
        string[number_new] = '\0';
    }
     

    free(h);
    free(matrix);
    return string;
    free(string);
}

void make_text(const char** text,char** new_text) {
    size_t number_text = strlen(*text);
    int number = 0;
    for (int i = 0;i < number_text;i++) {
        if (text[0][i] > 96 && text[0][i] < 123 && text[0][i] != 119) {
            new_text[0][number] = text[0][i] - 32;
        }
        else if (text[0][i] > 64 && text[0][i] < 91 && text[0][i] != 87) {
            new_text[0][number] = text[0][i];
        }
        else if (text[0][i] == 'w' || text[0][i] == 'W') {
            new_text[0][number] = 'V';
        }
        else {
            number--;
        }
        if (number != 0 && number % 2 != 0 && new_text[0][number - 1] == new_text[0][number] && new_text[0][number] != 'X') {
            new_text[0][number + 1] = new_text[0][number];
            new_text[0][number] = 'X';
            number++;
        }
        number++;
        new_text[0][number] = '\0';
        new_text[0][number + 1] = '\0';
    }
    new_text[0][number] = (strlen(*new_text) % 2 == 0) ? '\0' : 'X';
}
void make_matrix(char** key_edit,char*** matrix) {
    for (int i = 0; i < 5; i++) {
        matrix[0][i] = (char*)malloc(5 * sizeof(char));
        for (int j = 0; j < 5; j++) {
            matrix[0][i][j] = '\0';
        }
    }
    int number = 0;
    for (int i = 0;i < 5;i++) {
        for (int i2 = 0;i2 < 5;i2++) {
            if ((i * 5 + i2) < strlen(*key_edit)) {
                matrix[0][i][i2] = key_edit[0][i * 5 + i2];
            }
            else {
                matrix[0][i][i2] = ALPHA[number];
                for (int index = 0; index < strlen(*key_edit);index++) {
                    if (key_edit[0][index] == ALPHA[number]) {
                        if (i2 != 0) {
                            i2--;
                        }
                        else {
                            i--;
                            i2 = 4;
                        }
                    }
                }
                number++;
            }
        }
    }
}


void make_key(const char** key, char** result) {
   
    size_t len = strlen(*key);
    int idx = 0;
    for (int i = 0;i < len;i++) {
        if (key[0][i] >= 'a' && key[0][i] <= 'z' && key[0][i] != 'w') {
            result[0][idx] = key[0][i] - ' ';
            result[0][idx + 1] = '\0';
        }
        else if (key[0][i] >= 'A' && key[0][i] <= 'Z' && key[0][i] != 'W') {
            result[0][idx] = key[0][i];

        }
        else if (key[0][i] == 'w' || key[0][i] == 'W') {
            result[0][idx] = 'V';
        }
        else {
           idx--;
        }
        for (int k = 0; k < idx; k++) {
            if (result[0][idx] == result[0][k]) {
                result[0][idx] = '\0';
                idx--;
                break;
            }
          }
        idx++;
    }
}


//int main(){
//char *encrypted, *decrypted;

// even length of string
//encrypted = playfair_encrypt("Bolo zase ticho", "Ak by sme poveda oboch dobre nezlahodili mohol by sa napapreny vlk do nas oddat ale sprobujme im hodit po kusku slaniny s chlebom ");
//printf("%s\n", encrypted);
// "Hello world" --> "HELXLOVORLDX"
// IS JZ JQ XN TK JC
//decrypted = playfair_decrypt("SeCReT", encrypted);
//printf("%s\n", decrypted);
// HELXLOVORLDX
//free(encrypted);
//free(decrypted);

// odd length of string
//encrypted = playfair_encrypt("Este len svitat pocalo kralova dcera vysadla do koca", "Ale vies ty co");
//printf("%s\n", encrypted);
// "Hello" --> "HELXLO"
// JB RY DR
//decrypted = playfair_decrypt("world", encrypted);
//printf("%s\n", decrypted);
// HELXLO
//free(encrypted);
//free(decrypted);

// letter 'X' in message
//encrypted = playfair_encrypt("Password", "Taxi please");
//printf("%s\n", encrypted);
// "Taxi please" --> "TAXIPLEASE"
// UP YH AK DO OB
//decrypted = playfair_decrypt("vindicate", "NN UP EY FB NY");
//printf("%s\n", decrypted);
// TAXIPLEASE
//free(encrypted);
//free(decrypted);

// multi 'X's in message
//encrypted = playfair_encrypt("please", "Taxxxiii");
//printf("%s\n", encrypted);
// "Taxxxiii" --> "TAXXXIIXIX"
// RS EE VJ JV JV
//decrypted = playfair_decrypt("truckage", "UU YO UG OG VY");
//printf("%s\n", decrypted);
// TAXXXIIXIX
//free(encrypted);
//free(decrypted);

//return 0;
//}
