#include <string.h>
#include <stdio.h>
#include "container.h"
#include <stdlib.h>
#include <ctype.h>


struct container* destroy_containers(struct container* first){

while(first != NULL){
struct container* new_next = first -> next;
 if(first -> type == ROOM){
    destroy_room(first -> room);
  }
 else if(first -> type == ITEM){
    destroy_item(first -> item);
 }
 else if(first -> type == COMMAND){
    destroy_command(first -> command);
 }
 else if(first -> type == TEXT){
    if(first-> text !=  NULL){
     free(first-> text);
    }
 }
 free(first -> next);
 free(first);
 first = new_next;
 }
return NULL;
}


struct container* create_container(struct container* first, enum container_type type, void* entry){
  if(entry == NULL){
   return 0;
   }
  if(first != NULL){
      if(type != first -> type){
         return 0;
      }
  }
      struct container* new_c = calloc(1,sizeof(struct container)); 
      new_c -> type = type;
      if(type == ROOM){
       new_c -> room = entry;
      }
      else if(type == ITEM){
        new_c -> item = entry;
      }
      else if(type == COMMAND){
        new_c -> command = entry;
      }
      else if(type == TEXT){
        new_c -> text = entry;
      }
   if(first == NULL){
      new_c -> next =  NULL;
   }
   else{
      while(first -> next != NULL){
       first = first -> next;
      }
       first -> next = new_c;
   }
   return new_c;
}


void* get_from_container_by_name(struct container *first, const char *name){
 if(first == NULL || name == NULL){
 return NULL;
 }
 if (strlen(name) == 0){
  return NULL;
 }

  struct container *cont;
  char name_cont[100];
  char help[100];
  cont = first;
  strcpy(help, name);
  while(cont != NULL){
    if(cont -> type == ITEM || cont -> type == COMMAND || cont -> type == ROOM){
		strcpy(name_cont, cont -> room -> name);
	    if(!strcmp(name_cont, help)){
                  if(cont -> type == COMMAND) return cont -> command;
                  else if(cont -> type == ITEM) return cont -> item;
		  else if(cont -> type == ROOM) return cont -> room;
	      }
	    } 
      else {
		strcpy(name_cont, cont -> text);
		if(strstr(name_cont, help)){
	        return cont -> text;
	      }
     }
	    cont = cont -> next;
	  }
  return NULL;
}
struct container* remove_container(struct container *first, void *entry){

if(first == NULL){
  return NULL;
}

struct container* c = first;
struct container* p = NULL;
switch(first -> type){

  case ROOM:
    while(c != NULL){
     if(c -> room == entry){
      if(c == first){
         if(first -> next == NULL) return NULL;
         first = first -> next;
         free(c);
         return first;
       }
      else{
        p -> next = c -> next;
        free(c);
        return first;
        }        
      }
    p = c;
    c = c -> next;
    }

  case ITEM:
    while(c != NULL){
     if(c -> item == entry){
      if(c == first){
         if(first -> next == NULL) return NULL;
         first = first -> next;
         free(c);
         return first;
       }
      else{
        p -> next = c -> next;
        free(c);
        return first;
        }
      }
    p = c;
    c = c -> next;
    }

  case COMMAND:
    while(c != NULL){
     if(c -> command == entry){
      if(c == first){
         if(first -> next == NULL) return NULL;
         
         first = first -> next;
         free(c);
         return first;
       }
      else{
        p -> next = c -> next;
        free(c);
        return first;
        }
      }
    p = c;
    c = c -> next;
    }

  case TEXT:
    while(c != NULL){
     if(c -> text == entry){
      if(c == first){
       if(first -> next == NULL) return NULL;

         first = first -> next;
         free(c);
         return first;
       }
      else{
        p -> next = c -> next;
        free(c);
        return first;
        }
      }
    p = c;
    c = c -> next;
    }
 }
return first;
}
