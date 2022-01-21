#include "bmp.c"
#include "playfair.c"
#include <stdio.h>

int main(){

char *encrypted, *decrypted;

// even length of string
encrypted = playfair_encrypt("SeCReT", "Hello world");
printf("%s", encrypted);
// "Hello world" --> "HELXLOVORLDX"
// IS JZ JQ XN TK JC
decrypted = playfair_decrypt("SeCReT", encrypted);
printf("%s", decrypted);
// HELXLOVORLDX
free(encrypted);
free(decrypted);

// odd length of string
encrypted = playfair_encrypt("world", "Hello");
printf("%s", encrypted);
// "Hello" --> "HELXLO"
// JB RY DR
decrypted = playfair_decrypt("world", encrypted);
printf("%s", decrypted);
// HELXLO
free(encrypted);
free(decrypted);

// letter 'X' in message
encrypted = playfair_encrypt("Password", "Taxi please");
printf("%s", encrypted);
// "Taxi please" --> "TAXIPLEASE"
// UP YH AK DO OB
decrypted = playfair_decrypt("Password", encrypted);
printf("%s", decrypted);
// TAXIPLEASE
free(encrypted);
free(decrypted);

// multi 'X's in message
encrypted = playfair_encrypt("please", "Taxxxiii");
printf("%s", encrypted);
// "Taxxxiii" --> "TAXXXIIXIX"
// RS EE VJ JV JV
decrypted = playfair_decrypt("please", encrypted);
printf("%s", decrypted);
// TAXXXIIXIX
free(encrypted);
free(decrypted);

char* reversed = reverse("Hello world!");
printf("%s\n", reversed);

// basic test with long text
encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");
printf("%s\n", encrypted);
free(encrypted);

decrypted = vigenere_decrypt("CoMPuTeR", "JSXAI PSINR!");
printf("%s\n", decrypted);
free(decrypted);

unsigned char* encrypted2;
//xy basic test with long text
encrypted2 = bit_encrypt("Hello world!");
for(int i=0; i < 12;i++) {
    printf("%x ", encrypted2[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
}

char* dencrypted2;
//xy basic test with long text
dencrypted2 = bit_decrypt(encrypted2);
for(int i=0; i < 12;i++) {
    printf("%d ", dencrypted2[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
}

free(dencrypted2);
free(encrypted2);

unsigned char* a;
a = bmp_encrypt("SeCReT", "Hello world!");
for(int i=0; i < 12;i++) {
    printf("%x ", a[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
}

char* b;

b = bmp_decrypt("SeCReT",a);
for(int i=0; i < 12;i++) {
    printf("%c ", b[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
}


    return 0;
}
