#include <stdio.h>
#include "item.h"
#include <stdlib.h>
#include <string.h>

struct item* create_item(char* name, char* description, unsigned int properties){
  if(name == NULL || strlen(name) == 0 || description == NULL || strlen(description) == 0){
     return NULL;
  } 
  struct item* item = calloc(1,sizeof(struct item));
  item -> name = calloc(strlen(name) + 1,sizeof(char));
  strcpy(item -> name, name);
  item -> description =calloc(strlen(description) + 1,sizeof(char)); 
  strcpy(item -> description, description);
  item -> properties  = properties;

return item;
}

struct item* destroy_item(struct item* item){
  if(item == NULL){
   return NULL;
  }
  if(item -> name != NULL){
   free(item -> name);
  }  
 
  if(item -> description != NULL){
   free(item -> description);
  }
free(item);
return NULL;
}
