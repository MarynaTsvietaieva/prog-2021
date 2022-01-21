
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "hof.h" 


int compare(const void* left, const void* right){
    return (((struct player*)right)->score - ((struct player*)left)->score) + 1;
}

void sort_data(struct player list[], size_t *result){
    qsort(list, *result, sizeof(struct player), compare);
}

int load(struct player list[]){
 FILE *f = fopen(HOF_FILE,"r");
 if(f == NULL){
   return -1;
  }
  
 char str =  (char)fgetc(f);
  int i = 0;
  int j = 0;
  size_t result = 0;
  while(str != EOF && result != 10 ){
    
   if(j == 0 && str != ' '){
     list[result].name[i] = str;
     i++;
     }
   if(str == ' '){
      i++;
      j = i;
      str = (char)fgetc(f);
     }
    if(j != 0 && str != '\n' && str != EOF){
      list[result].score = list[result].score*10 + (int)(str-48);
      i++;
     }
    if(str == '\n'){
     result++;
     i=0;
     j = 0;
     }
 str = (char)fgetc(f);    
}

sort_data(list, &result);
fclose(f);
 return (int)result;
}

bool save(const struct player list[], const int size){
   FILE *f = fopen(HOF_FILE, "w");

   if(f == NULL){
      return false;
   }

   for(int i = 0; i < size; i++){
      fprintf(f,"%s %d\n", list[i].name, list[i].score);
   }
fclose(f);
return true;
}

bool add_player(struct player list[], int* size, const struct player player){
  if(list[*size-1].score > player.score && *size == 10){
    return false;
  }
   
  if(*size < 10){
   for(int i = 0; i < strlen(player.name); i++){
      list[*size].name[i] = player.name[i];
     } 
    list[*size].score = player.score;
    size_t result = (size_t)(*size+1);
    *size = *size+1;
    sort_data(list, &result);
  }
  else if(list[*size-1].score <= player.score && *size == 10){
   for(int i = 0; i < strlen(player.name)+1; i++){
    if(i < strlen( player.name)){
      list[*size-1].name[i] = player.name[i];
     }
    else{
      list[*size-1].name[i] = '\0';
     }
    }
    list[*size-1].score = player.score;
    size_t result = (size_t)(*size);
    sort_data(list, &result);
    
  } 
save(list,*size);
return true;
}


