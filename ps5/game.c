#include <stdio.h>
#include "backpack.h"
#include "command.h"
#include "container.h"
#include "game.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"
#include <string.h>
#include <stdlib.h>

void play_game(struct game* game){
 execute_command(game,NULL);
}

struct game* create_game(){
  struct game* game = calloc(1,sizeof(struct game));
  
  game -> state = PLAYING;
  game -> parser = create_parser();
  game -> world = create_world();
  game -> current_room  = game -> world -> room;
  game -> backpack = create_backpack(5);
return game;
}

struct game* destroy_game(struct game* game){
if(game != NULL){
     destroy_parser(game -> parser);
     destroy_world(game -> world);
     destroy_backpack(game -> backpack);
   free(game);
}
return NULL;    
}

void execute_command(struct game* game, struct command* command){
if(game == NULL || command == NULL){
 return;
}
if(!strcmp(command -> name, "KONIEC")){
 game -> state = GAMEOVER;
}
else if(!strcmp(command -> name, "SEVER")){
 if(game -> current_room -> north != NULL){
   game -> current_room = game -> current_room -> north;
 }
}
else if(!strcmp(command -> name, "JUH")){
 if(game -> current_room -> south != NULL){
 game -> current_room = game -> current_room -> south; 
 }
}
else if(!strcmp(command -> name, "VYCHOD")){
 if(game -> current_room -> east != NULL){
 game -> current_room = game -> current_room -> east;
}
}
else if(!strcmp(command -> name, "ZAPAD")){
 if(game -> current_room -> west != NULL){
 game -> current_room = game -> current_room -> west;
}
}

else if(!strcmp(command -> name, "RESTART")){
 game -> state = RESTART;
}
}

