#include <stdio.h>
#include "room.h"
#include <stdlib.h>
#include <string.h>


struct room* create_room(char *name, char *description){
  if(name == NULL || description == NULL){
   return NULL;
  }
  
  if(strlen(name) == 0 || strlen(description) == 0){
  return 0;
  }
  struct room *room = calloc(1,sizeof(struct room));
  room -> name = calloc(strlen(name) + 1, sizeof(char));
  strcpy(room -> name,name);
  room -> description = calloc(strlen(description) + 1, sizeof(char));
  strcpy(room -> description, description);
  
  return room;
}

struct room* destroy_room(struct room* room){
   if(room == NULL){
    return NULL;
   }
   if(room -> name != NULL){
     free(room -> name); 
   }
   if(room -> description != NULL){
    free(room -> description);
   }
   if(room -> north != NULL){
     free(room -> north);
   } 
   if(room -> south != NULL){
     free(room -> south);
   }
   if(room -> east != NULL){
     free(room -> east);
   }
   if(room -> west != NULL){
     free(room -> west);
   }
   if(room -> items != NULL){
     free(room -> items);
   }
 free(room);
 return NULL;
}


void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){

 if(room != NULL){
   
   if(south !=  room -> south){
     room -> south = south;
   } 
   if(north !=  room -> north){
      room -> north = north;
   }
   if(east !=  room -> east){
    room -> east = east;
   }
   if(west !=  room -> west){
     room -> west = west;
   }
 }
}


void add_item_to_room(struct room* room, struct item* item){
   if(room == NULL || item == NULL){
    }
   else{
      if(room -> items != NULL){
      create_container(room -> items, ROOM,item);
      }
      else{
       room -> items = create_container(room -> items, ROOM,item);
      }
    }
}


void delete_item_from_room(struct room* room, struct item* item){
  if(room != NULL && item != NULL){
   room -> items = remove_container(room -> items, item);
  }
}

struct item* get_item_from_room(const struct room* room, const char* name){
  if(room == NULL || name == NULL || strlen(name) < 1){
   return NULL;
  }
  else{
   return get_from_container_by_name(room -> items,name);  
   }
return NULL;
}

