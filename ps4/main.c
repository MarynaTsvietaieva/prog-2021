#include <stdio.h>
#include "bmp.h"
#include "transformations.h"
#include <stdlib.h>

int main(int argc, char **argv){

 FILE* f =  fopen(argv[1],"r");

  //FILE* f = NULL;
  struct bmp_image* image = read_bmp(f);
  //printf("%d\n",image ->data ->blue);
  printf("%d\n",image -> data[1].green);
  printf("%d\n",image -> data[1].red);
  printf("%d\n",image -> data[1].blue);

  printf("%d", write_bmp(f,image));
  if(flip_horizontally(image) != NULL){
  printf("%d\n",flip_horizontally(image) -> data[0].green);
  printf("%d\n",flip_horizontally(image) -> data[0].red);
  printf("%d\n",flip_horizontally(image) -> data[0].blue);
  }
  if(flip_vertically(image) != NULL){
  printf("%d\n",flip_vertically(image) -> data[0].green);
  printf("%d\n",flip_vertically(image) -> data[0].red);
  printf("%d\n",flip_vertically(image) -> data[0].blue);
  }
  if(rotate_right(image)!= NULL ){
  printf("%d\n",rotate_right(image) -> data[0].green);
  printf("%d\n",rotate_right(image) -> data[0].red);
  printf("%d\n",rotate_right(image) -> data[0].blue);
  }
  if(rotate_left(image) != NULL){
   printf("%d\n",rotate_left(image) -> data[0].blue);
  }
  if(crop(image,0,0,1,1) != NULL){
  printf("%d\n",crop(image,0,0,1,1) -> data[0].blue);
  }
  if(scale(image,(float)0.23) != NULL){
  printf("ok");
  }
 if(extract(image,"r") != NULL){
 printf("ok");
 }
  free_bmp_image(image);
  fclose(f);
 return 0;
}





