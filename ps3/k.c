#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game){
for(int i = 0; i < SIZE; i++){
  for (int j = 0;j < SIZE; j++){
    if(game.board[i][j] == 'K'){
      return true;
   }

  }
}
return false;
}

bool is_move_possible(const struct game game){
for(int i = 0; i < SIZE; i++){
  for (int j = 0;j < SIZE; j++){
   if(game.board[i][j] == ' '){
    return true;
   }
   if(i != SIZE - 1){
       if(j != SIZE - 1){
              if(game.board[i][j] == game.board[i][j+1] || game.board[i][j] == game.board[i+1][j]){
              return true;
               }
       }
       else{
              if(game.board[i][j] == game.board[i+1][j]){
              return true;
              }
      }
  }  
   else{
         if(j != SIZE-1){
            if(game.board[i][j] == game.board[i][j+1]){
                  return true;
                }
          }
     }
}
}
return false;
}


bool update(struct game *game, int dy, int dx){
  if((dy != 0  && dx != 0) || ( dx==0 && dy == 0)){
      return false;
  }
  bool result = false;
  if(dx == 1){

    for(int i = 0; i < SIZE; i++){
     for(int j = SIZE - 1; j > -1; j-- ){
       
       if(game->board[i][j] != ' '){
          int left = 1;
          while(game->board[i][j-left] == ' ' && j-left != -1){
             left++;
          }
         int right = 1;
         while(game->board[i][j+right] == ' ' && j+right != SIZE){
             right++;
          }
         right--;
          if(j-left != -1){
              if(game->board[i][j] == game->board[i][j-left]){
                  game->board[i][j+right] = (char)((int)game->board[i][j]+1);
                  result = true;
                  game->score += (int)powf(2,(float)((int)game->board[i][j+right]-64));
                  if(right != 0){
                      game->board[i][j] = ' ';
                  }  
                  game->board[i][j-left] = ' ';
              }
             else{
                      game->board[i][j+right] = game->board[i][j];
                     if(right != 0){
                       result = true;
                       game->board[i][j] = ' ';
                       }

              }

          }
        else{
          game->board[i][j+right] = game->board[i][j];
          if(right != 0){
            result = true;
            game->board[i][j] = ' ';
          }
       }
      }
  }
 }
}

if(dx == -1){

  for(int i = 0; i < SIZE; i++){
     for(int j = 0; j <SIZE ; j++ ){

       if(game->board[i][j] != ' '){
          int left = 1;
          while(game->board[i][j-left] == ' ' && j-left != -1){
             left++;
          }
         int right = 1;
         while(game->board[i][j+right] == ' ' && j+right != SIZE){
             right++;
          }
         left--;
          if(j+right != SIZE){
              if(game->board[i][j] == game->board[i][j+right]){
                  game->board[i][j-left] = (char)((int)game->board[i][j]+1);
                  result = true;
                  game->score += (int)powf(2,(float)((int)game->board[i][j-left]-64));
                  if(left != 0){
                      game->board[i][j] = ' ';
                  }
                  game->board[i][j+right] = ' ';
              }
          else{
          game->board[i][j-left] = game->board[i][j];
          if(left != 0){
            result = true;
            game->board[i][j] = ' ';
          }
       }


          }
        else{
          game->board[i][j-left] = game->board[i][j];
          if(left != 0){
            result = true;
            game->board[i][j] = ' ';
          }
       }
      }
  }
 }


}

if(dy == -1){
 for(int i = 0; i < SIZE; i++){
     for(int j = 0; j <SIZE ; j++ ){

       if(game->board[j][i] != ' '){
          int hor = 1;
          while(game->board[j-hor][i] == ' ' && j-hor != -1){
             hor++;
          }
         int dol = 1;
         while(game->board[j+dol][i] == ' ' && j+dol != SIZE){
             dol++;
          }
         hor--;
          if(j+dol != SIZE){
              if(game->board[j][i] == game->board[j+dol][i]){
                  game->board[j-hor][i] = (char)((int)game->board[j][i]+1);
                  result = true;
                  game->score += (int)powf(2,(float)((int)game->board[j-hor][i]-64));
                  if(hor != 0){
                      game->board[j][i] = ' ';
                  }
                  game->board[j+dol][i] = ' ';
              }

           else{
          game->board[j-hor][i] = game->board[j][i];
          if(hor != 0){
            result = true;
            game->board[j][i] = ' ';
          }
       }

          }
        else{
          game->board[j-hor][i] = game->board[j][i];
          if(hor != 0){
            result = true;
            game->board[j][i] = ' ';
          }
       }
      }
  }
 }
}

if(dy == 1){
 for(int i = 0; i < SIZE; i++){
     for(int j = SIZE-1; j > -1 ; j--){

       if(game->board[j][i] != ' '){
          int hor = 1;
          while(game->board[j-hor][i] == ' ' && j-hor != -1){
             hor++;
          }
         int dol = 1;
         while(game->board[j+dol][i] == ' ' && j+dol != SIZE){
             dol++;
          }
         dol--;
          if(j-hor != -1){
              if(game->board[j][i] == game->board[j-hor][i]){
                  game->board[j+dol][i] = (char)((int)game->board[j][i]+1);
                  result = true;
                  game->score += (int)powf(2,(float)((int)game->board[j+dol][i]-64));
                  if(dol != 0){
                      game->board[j][i] = ' ';
                  }
                  game->board[j-hor][i] = ' ';
              }
          else{
          game->board[j+dol][i] = game->board[j][i];
          if(dol != 0){
            result = true;
            game->board[j][i] = ' ';
          }
       }

          }
        else{
          game->board[j+dol][i] = game->board[j][i];
          if(dol != 0){
            result = true;
            game->board[j][i] = ' ';
          }
       }
      }
  }
 }
}

return result;
}


//int main(){

// another move is possible
//struct game game = {
//   .board = {
//          {'F', 'A', 'I', ' '},
//	{'B', 'H', ' ', ' '},
//	{' ', 'A', ' ', ' '},
//	{' ', 'F', ' ', ' '} },
//    .score = 0
//};

//bool result = update(&game, 0, 1);

//printf("%d\n",result);
//for(int i = 0; i < SIZE; i++){
//  for (int j = 0;j < SIZE; j++){
//     if(game.board[i][j] == ' '){
//      printf("_ ");
//     }
//     else{
//      printf("%c ",game.board[i][j]);
//     }
// }
// printf("\n");//
//}
//printf("score = %d\n",game.score);


//return 0;
//}
