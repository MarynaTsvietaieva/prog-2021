#include <stdbool.h>
#include <stdio.h>
#include "item.h"
#include "container.h"
#include "backpack.h"
#include <stdlib.h>


struct backpack* create_backpack(const int capacity){
  struct backpack* backpack = calloc(1, sizeof(struct backpack));
  backpack -> capacity = capacity;
  backpack -> size = 0;
  return backpack;
}

struct backpack* destroy_backpack(struct backpack* backpack){ 
  if(backpack != NULL){
    if(backpack -> items != NULL){
      destroy_containers(backpack -> items); 
    }
    free(backpack);
 }
return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item){
 if(backpack == NULL || item == NULL){
   return false;
 }
 if(backpack -> capacity <= backpack -> size){
   return false;
 }
 if(backpack -> items == NULL){
   backpack -> items = create_container(NULL, ITEM, item);
 }
 else{
   create_container(backpack -> items, ITEM, item);
 }
 backpack -> size += 1;
 return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
if(backpack != NULL && item != NULL){
   backpack -> items = remove_container(backpack -> items, item);
   backpack -> size -= 1;
 }
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
  if(backpack == NULL || name == NULL){
     return NULL;
  }  
  return get_from_container_by_name(backpack -> items, name); 
}
