#include <stdio.h>
#include "world.h"


struct container* create_world(){
  struct room* room1 = create_room("Start","This is where your adventure begine");  
  struct room* room2 = create_room("Bar","You find yourself in a country bar");
  struct room* room3 = create_room("Bar veranda","Look around for a map for your adventure");
  struct room* room4 = create_room("South road","The road from the bar to the city center");
  struct room* room5 = create_room("Western road","The road from the bar to the forest");
  struct room* room6 = create_room("East road","The road from the bar to the widow");
  struct room* room7 = create_room("City center","A great place to choose a weapon for battle");
  struct room* room11 = create_room("Home","You can take food from home, suddenly it will come in handy");
  struct room* room9 = create_room("Forest","Perhaps an ordinary forest, perhaps not");
  struct room* room10 = create_room("Southeast road","The road from widow to home");
  struct room* room8 = create_room("Widow's house","The widow says that her husband was killed by a monster in the forest and asks for revenge. You immediately thought that you can lure the monster with food");
  struct room* room12 = create_room("bridge","The road from home to the city center");
  struct room* room13 = create_room("field","Road from the city center to the inn");
  struct room* room14 = create_room("Inn","Here you are offered to exchange a card for armor");
  struct room* room15 = create_room("southwest road","The road from the inn to the forest");
  
  set_exits_from_room(room1,NULL,room2,NULL,NULL);
  set_exits_from_room(room2,room1,room3,NULL,NULL);
  set_exits_from_room(room3,room2,room4,room6,room5);
  set_exits_from_room(room4,room3,room7,NULL,NULL);
  set_exits_from_room(room5,NULL,NULL,room3,room9);
  set_exits_from_room(room6,NULL,NULL,room8,room3);
  set_exits_from_room(room7,room4,NULL,room12,room13);
  set_exits_from_room(room8,NULL,room10,NULL,room6);
  set_exits_from_room(room9,NULL,room15,room5,NULL);
  set_exits_from_room(room10,room8,room11,NULL,NULL);
  set_exits_from_room(room11,room10,NULL,NULL,room12);
  set_exits_from_room(room12,NULL,NULL,room11,room7);
  set_exits_from_room(room13,NULL,NULL,room7,room14);
  set_exits_from_room(room14,room15,NULL,room13,NULL);
  set_exits_from_room(room15,room9,room14,NULL,NULL);

  struct item* item1 = create_item("Homemade food","Just food",MOVABLE | USABLE);
  struct item* item2 = create_item("Fire sword","Good melee weapon",MOVABLE | USABLE);
  struct item* item3 = create_item("Wooden bow","Good weapon for long range combat", MOVABLE | USABLE);
  struct item* item4 = create_item("County map","County map", MOVABLE);
  struct item* item5 = create_item("Iron armor","Strong but very heavy", MOVABLE | USABLE);

  room11->items = create_container(room11->items, ITEM, item1);
  room7->items =  create_container(room7->items, ITEM, item2);
  room7->items->next = create_container(room7->items->next, ITEM, item3);
  room3->items = create_container(room3->items, ITEM, item4);
  room14->items = create_container(room14->items, ITEM, item5);

  struct container* rooms = add_room_to_world(NULL, room1);

  add_room_to_world(rooms, room2);
  add_room_to_world(rooms, room3);
  add_room_to_world(rooms, room4);
  add_room_to_world(rooms, room5);
  add_room_to_world(rooms, room6);
  add_room_to_world(rooms, room7);
  add_room_to_world(rooms, room8);
  add_room_to_world(rooms, room9);
  add_room_to_world(rooms, room10);
  add_room_to_world(rooms, room11);
  add_room_to_world(rooms, room12);
  add_room_to_world(rooms, room13);
  add_room_to_world(rooms, room14);
  add_room_to_world(rooms, room15);


return rooms;
}

struct container* add_room_to_world(struct container* world, struct room* room){
 if(room == NULL){
   return NULL;
 }
 if(world == NULL){
    struct container* svet = create_container(NULL, ROOM, room);
    return svet;
  }
 else{
     if(get_room(world, room -> name) == NULL){
        struct container* svet = create_container(world, ROOM, room);
        return svet;

     }
   
  }
return NULL;
}

struct container* destroy_world(struct container* world){
  if(world != NULL){
   destroy_containers(world);
  }
return NULL;
}

struct room* get_room(struct container* world, char* name){
   if(world == NULL || name == NULL){
     return NULL;
   }

   return get_from_container_by_name(world, name);
}

