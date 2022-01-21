#include <stdio.h>
#include "command.h"
#include <stdlib.h>
#include <string.h>

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){

if(name == NULL || description == NULL){
return NULL;
}

if(strlen(name) == 0 || strlen(description) == 0){
  return NULL;
}

struct command* command = calloc(1,sizeof(struct command));

command -> name  = calloc(strlen(name) + 1, sizeof(char));
strcpy(command -> name,name);

command -> description  = calloc(strlen(description)+1, sizeof(char));
strcpy(command -> description ,description);

command -> nmatch = nmatch;  

if(pattern != NULL){
  command -> groups = &pattern;
  regex_t r;
  regcomp(&r, pattern, REG_ICASE);
  command -> preg = r;
}
return command;
}

struct command* destroy_command(struct command* command){
  if(command == NULL){
  return NULL;
  }
  if(command -> name != NULL){
   free(command -> name);
  }
 if(command -> description != NULL){
   free(command -> description);
  }
  free(command);
return NULL;
}

