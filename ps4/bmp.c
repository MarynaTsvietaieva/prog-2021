#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmp.h"
#include <string.h>


struct bmp_header* read_bmp_header(FILE* stream){
if(stream == NULL){
 return 0;
}
struct bmp_header* header = calloc(1,sizeof(struct bmp_header));
if(fseek(stream, 54,SEEK_SET) != 0){
  free(header);
  return NULL;
}

fseek(stream, 0,SEEK_SET);
if(fread(&header -> type, 2, 1 ,stream) != 1){
   free(header);
   return NULL;
}
//printf("%d\n",header -> type);
if(header -> type != 19778){
  free(header);
  return NULL;
}
fseek(stream, 18,SEEK_SET);

if(fread(&header -> width, 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}
//printf("%d\n",header -> width);
if(header -> width <= 0 || header -> width > 10000){
  free(header);
  return NULL;
}

fseek(stream, 22,SEEK_SET);

if(fread(&header -> height, 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}
//printf("%d\n",header -> height);

if(header -> height <= 0 || header -> height > 10000){
  free(header);
  return NULL;
}

fseek(stream, 2,SEEK_SET);

if(fread(&header -> size, 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

//printf("%d\n",header -> size);

fseek(stream, 28,SEEK_SET);

if(fread(&header -> bpp, 2, 1 ,stream) != 1){
   free(header);
   return NULL;
}

//printf("%d\n",header -> bpp);
uint32_t medz = 0;
if(((header -> bpp/8) * header -> width) % 4 != 0){
  medz =  (uint32_t)4 - (((header -> bpp/8) * header -> width)%4);
}

if(header -> size != (medz + header ->width*(header ->bpp/8))*header -> height + 54){
        free(header);
        return NULL;
}

fseek(stream, 34,SEEK_SET);

if(fread(&header -> image_size, 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

if(header -> image_size != (medz + header ->width*(header ->bpp/8))*header -> height){
        free(header);
        return NULL;
}

fseek(stream, 6,SEEK_SET);

if(fread(&header -> reserved1, 2, 1 ,stream) != 1){
   free(header);
   return NULL;
}

fseek(stream, 8,SEEK_SET);

if(fread(&header -> reserved2, 2, 1 ,stream) != 1){
   free(header);
   return NULL;
}

fseek(stream, 10,SEEK_SET);

if(fread(&header -> offset, 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

if(header -> offset != 54){
   free(header);
   return NULL;
}

fseek(stream, 14,SEEK_SET);

if(fread(&header -> dib_size, 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

if(header -> dib_size != 40){
  free(header);
  return NULL;
}

fseek(stream, 26,SEEK_SET);

if(fread(&header -> planes , 2, 1 ,stream) != 1){
   free(header);
   return NULL;
}

if(header -> planes != 1){
  free(header);
  return NULL;
}

fseek(stream, 30,SEEK_SET);

if(fread(&header -> compression , 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

if(header -> compression != 0 && header -> compression != 1 && header -> compression != 2){
  free(header);
  return NULL;
}

fseek(stream, 38,SEEK_SET);

if(fread(&header -> x_ppm , 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

fseek(stream, 42,SEEK_SET);
if(fread(&header -> y_ppm , 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

fseek(stream, 46,SEEK_SET);

if(fread(&header -> num_colors , 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

fseek(stream, 50,SEEK_SET);

if(fread(&header -> important_colors , 4, 1 ,stream) != 1){
   free(header);
   return NULL;
}

return header;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header){

  if(stream != NULL && header != NULL){
    uint32_t h = header -> height;
    uint32_t w = header -> width;
    struct pixel* data = calloc(h*w, sizeof(struct pixel));


    fseek(stream,54, SEEK_SET);
    //printf("%ld jop\n",sizeof (struct pixel));
    for(int i = 0; i < h; i++){
     for(int j = 0; j < w; j++){
       fread(&data[j+(i*(int)w)],3, 1, stream);
       }
     fseek(stream,w%4,SEEK_CUR);
    }
    return data;
 }
return NULL;
}


struct bmp_image* read_bmp(FILE* stream){
  if(stream == NULL){
   return NULL;
   }
    struct bmp_image* image = calloc(1,sizeof(struct bmp_image));

    image -> header = read_bmp_header(stream);
 
    if(image -> header == NULL){
      fprintf(stderr,"Error: This is not a BMP file.\n");
      free(image);
      return NULL;
    }
    
    image -> data = read_data(stream, image -> header);

    if(image -> data == NULL){
     fprintf(stderr,"Error: Corrupted BMP file.\n");
     free(image);
     return NULL;
    }
    return image;  
}

bool write_bmp(FILE* stream, const struct bmp_image* image){

  if(stream != NULL && image -> header != NULL && image -> data != NULL){
     fwrite(image -> header, 54 , 1 ,stream);
     fwrite(image -> data, image -> header -> image_size, 1, stream);
     return 1;
   }
  
  return 0;
}


void free_bmp_image(struct bmp_image* image){
if(image != NULL){
   if(image -> header != NULL){
   free(image -> header);
   }
   if(image -> data != NULL){
   free(image -> data);
   }
   free(image);
   }
}

//int main(int argc, char **argv){

// FILE* f =  fopen(argv[1],"r");
   
  //FILE* f = NULL;
//  struct bmp_image* image = read_bmp(f);
  //printf("%d\n",image ->data ->blue);
//  struct bmp_header* header = read_bmp_header(f);
//  if(header != NULL){
//    printf("%d\n",header->type);
    //printf("%d\n",header->size);
    //printf("%d\n",header->reserved1);
    //printf("%d\n",header->reserved2);
    //printf("%d\n",header->offset);
    //printf("%d\n",header->dib_size);
    //printf("%d\n",header->width);
    //printf("%d\n",header->height);
    //printf("%d\n",header->planes);
    //printf("%d\n",header->bpp);
    //printf("%d\n",header->compression);
    //printf("%d\n",header->image_size);
    //printf("%d\n",header->x_ppm);
    //printf("%d\n",header->y_ppm);
    //printf("%d\n",header->num_colors);
    //printf("%d\n",header->important_colors);
//   printf("ok");
//  }
//  else{
//    printf("not ok");
//  }

//  printf("%d", write_bmp(f,image));

//  free_bmp_image(image);
//  fclose(f);
// return 0;
//}
