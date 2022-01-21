#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "backpack.h"
#include "command.h"
#include "container.h"
#include "game.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"

int main(){

struct game* game = create_game();
struct parser* parser = create_parser();
play_game(game);
/*
 * Inside of the function create and add commands to the list of existing commands
 *
 */

 // parse input in the game loop
 char* input = "ROZHLIADNI SA";
 struct command* cmd = parse_input(parser, input);
 if(cmd != NULL){
  printf("ok\n");
  }
  else{
  printf("not ok");
  }
 // cmd now should have reference to the command "VERZIA"

// if input is unknown, parsing will return NULL
// char* unknown_input = "   CO JE V MIESTNOSTI?  ";
// struct command*  cmd = parse_input(parser, unknown_input);
//  if(cmd == NULL){
//  printf("ok na NULL\n");
//  }
 // cmd = NULL;

// destroy parser at the end of game
parser = destroy_parser(parser);
char* text1 = "Hello";
char* text2 = "gamer";

struct container *first = create_container(NULL, TEXT, text1);
struct container *second = create_container(first, TEXT, text2);

printf("TEXT:\t%s\n", first->text);
printf("TEXT:\t%p\n", first->next);
printf("TEXT:\t%s\n", second->text);


if(get_from_container_by_name(first,"gamer") != NULL){
  printf("ok1\n");
  struct container *new_second =  get_from_container_by_name(first,"gamer");
  printf("TEXT:\t%s\n", new_second  -> text);

}

struct container* cont = remove_container(first, "gamer");
if(cont != NULL){
  if(cont -> next == NULL){
    printf("ok2");
  }
}

destroy_containers(cont);

struct room* new_room = create_room("hello","gamer");
if(new_room == NULL){
  printf("ok");
}
else{
 printf("%s\n %s\n",new_room -> name, new_room -> description );
}
set_exits_from_room(new_room,NULL,NULL,NULL,NULL);

struct room* home = create_room("start", "Nachadzas sa v chyzi svarneho suhaja. Na vychode sa nachadzaju dvere veduce z chyze von.");
add_item_to_room(home, NULL);
struct item* item = get_item_from_room(home, "zlaty KLUC");
if(item == NULL){
  printf("po");
}
struct item* key = create_item("zlaty KLUC","zlaty KLUC",0);
delete_item_from_room(home, NULL);
struct backpack* backpack = create_backpack(5);
if(backpack -> capacity == 5){
printf("ok");
}

if(add_item_to_backpack(backpack, key) == 1){
printf("ok");
}
delete_item_from_backpack(backpack, key);
if( get_item_from_backpack(backpack, "zlaty KLUC") == NULL){
printf("ok");
}

struct container* world = create_world();
if(world != NULL){
printf("ok");
}
struct container* add = add_room_to_world(world, home);
if(add != NULL){
printf("ok");
}
if(destroy_game(game)){
printf("ok");
}
struct command * command = create_command("start", "Nachadzas sa v chyzi svarneho suhaja. Na vychode sa nachadzaju dvere veduce z chyze von.", "(start)", 0);
if(command != NULL){
printf("ok");
}

return 0;
}
