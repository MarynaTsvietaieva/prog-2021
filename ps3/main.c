#include <stdio.h>
#include "k.h"
#include <stdlib.h>
#include "hof.h" 
#include "ui.h"

int main(){

struct game game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'}
     },
    .score = 1234
};

printf("is won: %d\n", is_game_won(game));
printf("is move possible: %d\n", is_move_possible(game));
bool result = update(&game, 0, -1);
printf("%d\n",result);
for(int i = 0; i < SIZE; i++){
  for (int j = 0;j < SIZE; j++){
     if(game.board[i][j] == ' '){
      printf("_ ");
     }
     else{
      printf("%c ",game.board[i][j]);
     }
 }
 printf("\n");
}
printf("score = %d\n",game.score);
render(game);
add_random_tile(&game);
struct player *list = calloc(11,sizeof(struct player));
struct player player = {
    .name = "john",
    .score = 100
};
int size = load(list);
bool result2 = add_player(list, &size, player);
printf("%d", result2);
free(list);
return 0;
}
