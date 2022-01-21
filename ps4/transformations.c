#include <stdio.h>
#include <stdlib.h>
#include "transformations.h"
#include <math.h>
#include <string.h>

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep) {
if(image != NULL && colors_to_keep != NULL){
 if(image -> header == NULL || image ->data == NULL){
  return NULL;
 }

bool r = 0;
bool b = 0;
bool g = 0;
 for(int i = 0; i < strlen(colors_to_keep); i++){
   if(colors_to_keep[i] != 'r' && colors_to_keep[i] != 'g' && colors_to_keep[i] != 'b'){
    return NULL;
   }

   if(colors_to_keep[i] == 'r' && r == 0){
    r = 1;
   }
   else if(colors_to_keep[i] == 'r'){
   return NULL;
   }

  if(colors_to_keep[i] == 'g' && g == 0){
    g = 1;
   }
   else if(colors_to_keep[i] == 'g'){
   return NULL;
   }

 if(colors_to_keep[i] == 'b' && b == 0){
    b = 1;
   }
   else if(colors_to_keep[i] == 'b'){
   return NULL;
   }
  }

  struct bmp_image* image_hor = calloc(1,sizeof(struct bmp_image));
  image_hor -> header = calloc(1,sizeof(struct bmp_header));

       if(image -> header->type != 19778){
        free(image_hor);
        return NULL;
       }
       image_hor -> header->type = image -> header->type;
       image_hor -> header->size = image -> header->size;
       image_hor -> header->reserved1 = image -> header->reserved1;
       image_hor -> header->reserved2 = image -> header->reserved2;
        if(image -> header->offset != 54){
        free(image_hor);
         //printf("jpo3");
         return NULL;
       }
       image_hor -> header->offset = image -> header->offset;
       if( image -> header->dib_size != 40){
         free(image_hor);
         //printf("jpo4");
         return NULL;
       }
       image_hor -> header->dib_size = image -> header->dib_size;
       if(image -> header->width <= 0 || image -> header->width > 10000){
         free(image_hor);
         //printf("jpo5");
         return NULL;
       }
       image_hor -> header->width = image -> header->width;
       if(image -> header->height <= 0 || image -> header->height > 10000){
         //printf("jpo6");
         free(image_hor);
         return NULL;
       }
       image_hor -> header->height = image -> header->height;
       image_hor -> header->planes = image -> header->planes;
       if(image -> header-> bpp != 1 && image -> header->bpp != 4 && image -> header->bpp != 8 && image -> header->bpp != 24){
         //printf("%d\n",image -> header-> bpp);
         free(image_hor);
         return NULL;
       }
       image_hor -> header->bpp = image -> header->bpp;
       if(image -> header-> compression != 1 && image -> header->compression != 0 && image -> header->compression != 2){
         //printf("%d\n",image -> header-> bpp);
          free(image_hor);
         return NULL;
       }
       image_hor -> header->compression = image -> header->compression;
       image_hor -> header->image_size = image -> header->image_size;
       image_hor -> header->x_ppm = image -> header->x_ppm;
       image_hor -> header->y_ppm = image -> header->y_ppm;
       image_hor -> header->num_colors = image -> header->num_colors;
       image_hor -> header->important_colors = image -> header->important_colors;

       size_t w = (size_t)image_hor -> header-> width;
       size_t h = (size_t)image_hor -> header -> height;

  image_hor -> data = calloc(w*h ,sizeof(struct pixel));

  for(size_t i = 0; i < h; i++){
    for(size_t j = 0; j < w; j++){
        image_hor -> data[j + w*i].red = (r == 1) ? image -> data[j + w*i].red : 0;
        image_hor -> data[j + w*i].green = (g == 1) ? image -> data[j + w*i].green : 0;
        image_hor -> data[j + w*i].blue = (b == 1) ? image -> data[j + w*i].blue : 0;
            //printf("%ld %ld\n",(j + w*i), (-j-1 + w*(i+1)));
            //printf("me %d\n",image_hor -> data[j + (int)(image -> header ->
         }
     }
  //printf("kk");
  return image_hor;
}
return NULL;
}


struct bmp_image* scale(const struct bmp_image* image, float factor){
  if(image != NULL && factor > 0){
   if(image -> header == NULL || image -> data == NULL){
     return NULL;
   }

   struct bmp_image* image_hor = calloc(1,sizeof(struct bmp_image));
   image_hor -> header = calloc(1,sizeof(struct bmp_header));
   if(image -> header->type != 19778){
      //printf("jpo2");
      free(image_hor);
       return NULL;
    }
   image_hor -> header->type = image -> header->type;
   image_hor -> header->reserved1 = image -> header->reserved1;
   image_hor -> header->reserved2 = image -> header->reserved2;
   if(image -> header->offset != 54){
         //printf("jpo3");
         free(image_hor);
         return NULL;
   }
   image_hor -> header->offset = image -> header->offset;
   if( image -> header->dib_size != 40){
         //printf("jpo4");
         free(image_hor);
         return NULL;
   }
   image_hor -> header->dib_size = image -> header->dib_size;
   if(image -> header->width <= 0 || image -> header->width > 10000){
         //printf("jpo5");
         free(image_hor);
         return NULL;
    }
   if(image -> header->height <= 0 || image -> header->height > 10000){
         //printf("jpo6");
          free(image_hor);
          return NULL;
    }
   image_hor -> header->planes = image -> header->planes;
   if(image -> header-> bpp != 1 && image -> header->bpp != 4 && image -> header->bpp != 8 && image -> header->bpp != 24){
         //printf("%d\n",image -> header-> bpp);
          free(image_hor);
         return NULL;
    }
   image_hor -> header->bpp = image -> header->bpp;
   if(image -> header-> compression != 1 && image -> header->compression != 0 && image -> header->compression != 2){
         //printf("%d\n",image -> header-> bpp);
         free(image_hor);
         return NULL;
   }
   image_hor -> header->compression = image -> header->compression;
   image_hor -> header->x_ppm = image -> header->x_ppm;
   image_hor -> header->y_ppm = image -> header->y_ppm;
   image_hor -> header->num_colors = image -> header->num_colors;
   image_hor -> header->important_colors = image -> header->important_colors;

   uint32_t height = (uint32_t)round((float)(image -> header  -> height)*factor);
   uint32_t width = (uint32_t)round((float)(image -> header  -> width)*factor);

   image_hor -> header  -> height = height;
   image_hor -> header  -> width = width;
   uint32_t medz = 0;
   if((width*(image_hor ->header -> bpp /8))%4 != 0){
          medz = 4 - width*(image_hor ->header -> bpp /8)%4;
    }

   image_hor ->header -> image_size = height*(width*(image_hor ->header -> bpp/8)+medz);
   image_hor ->header -> size =  image_hor ->header -> image_size + 54;

   image_hor -> data = calloc(width*height ,sizeof(struct pixel));
   uint32_t w = image->header->width;
   uint32_t h = image->header->height;
   for(uint32_t i = 0; i < height; i++){
    for(uint32_t j = 0; j < width; j++){
     image_hor -> data[i*width + j].red = image -> data[(i*h/height)*w + (j*w/width)].red;
     image_hor -> data[i*width + j].blue = image -> data[(i*h/height)*w + (j*w/width)].blue;
     image_hor -> data[i*width + j].green = image -> data[(i*h/height)*w + (j*w/width)].green;
    }
   }
   return image_hor;


  }
 return NULL;
}

struct bmp_image* flip_horizontally(const struct bmp_image* image){
    if(image != NULL){

      if(image -> header == NULL || image -> data == NULL){
         //printf("jpo1");
         return NULL;
       }
       struct bmp_image* image_hor = calloc(1,sizeof(struct bmp_image));
       image_hor -> header = calloc(1,sizeof(struct bmp_header));
       if(image -> header->type != 19778){
        free(image_hor);
        //printf("jpo2");
        return NULL;
       }
       image_hor -> header->type = image -> header->type;
       image_hor -> header->size = image -> header->size;
       image_hor -> header->reserved1 = image -> header->reserved1;
       image_hor -> header->reserved2 = image -> header->reserved2;
        if(image -> header->offset != 54){
        free(image_hor);
         //printf("jpo3");
         return NULL;
       }
       image_hor -> header->offset = image -> header->offset;
       if( image -> header->dib_size != 40){
         free(image_hor);
         //printf("jpo4");
         return NULL;
       }
       image_hor -> header->dib_size = image -> header->dib_size;
       if(image -> header->width <= 0 || image -> header->width > 10000){
         free(image_hor);
         //printf("jpo5");
         return NULL;
       }
       image_hor -> header->width = image -> header->width;
       if(image -> header->height <= 0 || image -> header->height > 10000){
         //printf("jpo6");
         free(image_hor);
         return NULL;
       }
       image_hor -> header->height = image -> header->height;
       image_hor -> header->planes = image -> header->planes;
       if(image -> header-> bpp != 1 && image -> header->bpp != 4 && image -> header->bpp != 8 && image -> header->bpp != 24){
         //printf("%d\n",image -> header-> bpp);
         free(image_hor);
         return NULL;
       }
       image_hor -> header->bpp = image -> header->bpp;
       if(image -> header-> compression != 1 && image -> header->compression != 0 && image -> header->compression != 2){
         //printf("%d\n",image -> header-> bpp);
          free(image_hor);
         return NULL;
       }
       image_hor -> header->compression = image -> header->compression;
       image_hor -> header->image_size = image -> header->image_size;
       image_hor -> header->x_ppm = image -> header->x_ppm;
       image_hor -> header->y_ppm = image -> header->y_ppm;
       image_hor -> header->num_colors = image -> header->num_colors;
       image_hor -> header->important_colors = image -> header->important_colors;

       size_t w = (size_t)image_hor -> header-> width;
       size_t h = (size_t)image_hor -> header -> height;
       image_hor -> data = calloc(w*h ,sizeof(struct pixel));
       //printf("%ld %ld\n",h,w);
       for(size_t i = 0; i < h; i++){
          for(size_t j = 0; j < w; j++){
            image_hor -> data[j + w*i].red = image -> data[-j-1 + w*(i+1)].red;
            image_hor -> data[j + w*i].green = image -> data[-j-1 + w*(i+1)].green;
            image_hor -> data[j + w*i].blue = image -> data[-j-1 + w*(i+1)].blue;
            //printf("%ld %ld\n",(j + w*i), (-j-1 + w*(i+1)));
            //printf("me %d\n",image_hor -> data[j + (int)(image -> header ->
         }
       }
       return image_hor;
    }
return NULL;
}


struct bmp_image* flip_vertically(const struct bmp_image* image){
      if(image != NULL){

      if(image -> header == NULL || image -> data == NULL){
         //printf("jpo1");
         return NULL;
       }
       struct bmp_image* image_hor = calloc(1,sizeof(struct bmp_image));
       image_hor -> header = calloc(1,sizeof(struct bmp_header));
       if(image -> header->type != 19778){
        //printf("jpo2");
        free(image_hor);
        return NULL;
       }
       image_hor -> header->type = image -> header->type;
       image_hor -> header->size = image -> header->size;
       image_hor -> header->reserved1 = image -> header->reserved1;
       image_hor -> header->reserved2 = image -> header->reserved2;
        if(image -> header->offset != 54){
         //printf("jpo3");
         free(image_hor);
         return NULL;
       }
       image_hor -> header->offset = image -> header->offset;
       if( image -> header->dib_size != 40){
         //printf("jpo4");
         free(image_hor);
         return NULL;
       }
       image_hor -> header->dib_size = image -> header->dib_size;
       if(image -> header->width <= 0 || image -> header->width > 10000){
         //printf("jpo5");
        free(image_hor);
         return NULL;
       }
       image_hor -> header->width = image -> header->width;
       if(image -> header->height <= 0 || image -> header->height > 10000){
         //printf("jpo6");
          free(image_hor);
         return NULL;
       }
       image_hor -> header->height = image -> header->height;
       image_hor -> header->planes = image -> header->planes;
       if(image -> header-> bpp != 1 && image -> header->bpp != 4 && image -> header->bpp != 8 && image -> header->bpp != 24){
         //printf("%d\n",image -> header-> bpp);
          free(image_hor);
         return NULL;
       }
       image_hor -> header->bpp = image -> header->bpp;
       if(image -> header-> compression != 1 && image -> header->compression != 0 && image -> header->compression != 2){
         //printf("%d\n",image -> header-> bpp);
         free(image_hor);
         return NULL;
       }
       image_hor -> header->compression = image -> header->compression;
       image_hor -> header->image_size = image -> header->image_size;
       image_hor -> header->x_ppm = image -> header->x_ppm;
       image_hor -> header->y_ppm = image -> header->y_ppm;
       image_hor -> header->num_colors = image -> header->num_colors;
       image_hor -> header->important_colors = image -> header->important_colors;
     
       image_hor -> data = calloc(image -> header -> width*image -> header -> height ,sizeof(struct pixel));
        for(int i = 0; i < image -> header -> height; i++){
          for(int j = 0; j < image -> header -> width; j++){
            image_hor -> data[j + (int)(image -> header -> width)*i].red = image -> data[j + (int)(image -> header -> width)*((int)(image -> header -> height) -1 -i)].red;
            image_hor -> data[j + (int)(image -> header -> width)*i].green = image -> data[ j + (int)(image -> header -> width)*((int)(image -> header -> height) -1 -i)].green;
            image_hor -> data[j + (int)(image -> header -> width)*i].blue = image -> data[j + (int)(image -> header -> width)*((int)(image -> header -> height) -1 -i)].blue;
            //printf("me %d\n",image_hor -> data[j + (int)(image -> header -> width)*i].green );
         }
       }
       return image_hor;
    }
return NULL;
}

struct bmp_image* rotate_right(const struct bmp_image* image){
   if(image != NULL){

       if(image -> header == NULL || image -> data == NULL){
         //printf("jpo1");
         return NULL;
       }
       struct bmp_image* image_hor = calloc(1,sizeof(struct bmp_image));
       image_hor -> header = calloc(1,sizeof(struct bmp_header));
       if(image -> header->type != 19778){
        //printf("jpo2");
        free(image_hor);
        return NULL;
       }
       image_hor -> header->type = image -> header->type;
       image_hor -> header->reserved1 = image -> header->reserved1;
       image_hor -> header->reserved2 = image -> header->reserved2;
        if(image -> header->offset != 54){
         //printf("jpo3");
         free(image_hor);
         return NULL;
       }
       image_hor -> header->offset = image -> header->offset;
       if( image -> header->dib_size != 40){
         //printf("jpo4");
         free(image_hor);
         return NULL;
       }
       image_hor -> header->dib_size = image -> header->dib_size;
       if(image -> header->width <= 0 || image -> header->width > 10000){
         //printf("jpo5");
        free(image_hor);
         return NULL;
       }
       image_hor -> header-> height = image -> header->width;
       if(image -> header->height <= 0 || image -> header->height > 10000){
         //printf("jpo6");
          free(image_hor);
         return NULL;
       }
       image_hor -> header->width = image -> header-> height;
       image_hor -> header->planes = image -> header->planes;
       if(image -> header-> bpp != 1 && image -> header->bpp != 4 && image -> header->bpp != 8 && image -> header->bpp != 24){
         //printf("%d\n",image -> header-> bpp);
          free(image_hor);
         return NULL;
       }
       image_hor -> header->bpp = image -> header->bpp;
       if(image -> header-> compression != 1 && image -> header->compression != 0 && image -> header->compression != 2){
         //printf("%d\n",image -> header-> bpp);
         free(image_hor);
         return NULL;
       }
       image_hor -> header->compression = image -> header->compression;
       image_hor -> header->x_ppm = image -> header->x_ppm;
       image_hor -> header->y_ppm = image -> header->y_ppm;
       image_hor -> header->num_colors = image -> header->num_colors;
       image_hor -> header->important_colors = image -> header->important_colors;

       uint32_t height = image -> header->width;
       uint32_t width = image -> header->height;
       image_hor -> data = calloc(width*height ,sizeof(struct pixel));
       uint32_t medz = 0;
       if((width*(image_hor ->header -> bpp /8))%4 != 0){
          medz = 4 - width*(image_hor ->header -> bpp /8)%4;
       }

       image_hor ->header -> image_size = height*(width*(image_hor ->header -> bpp/8)+medz);
       image_hor ->header -> size =  image_hor ->header -> image_size + 54;
       //pritnf("%d %d"image -> header -> width,image -> header -> height);
       for(int i = 0; i < height; i++){
          for(int j = 0; j < width; j++){
            image_hor -> data[j + (int)width*i].red = image -> data[((int)height*(j+1) - i -1)].red;
            image_hor -> data[j + (int)width*i].green = image -> data[(int)height*(j+1) - i -1].green;
            image_hor -> data[j + (int)width*i].blue = image -> data[(int)height*(j+1) - i -1].blue;
            //printf("me %d\n",image_hor -> data[j + (int)(image -> header -> width)*i].green );

         }
       }
      // printf("%d - %d;%d - %d %d\n",image_hor -> header-> width,image -> header-> width,image_hor -> header -> height,image -> header -> height,image_hor ->header -> size);
       return image_hor;
    }
return NULL;
}

struct bmp_image* rotate_left(const struct bmp_image* image){

 if(image != NULL){
  
       if(image -> header == NULL || image -> data == NULL){
         return NULL;
       }
       struct bmp_image* image_hor = calloc(1,sizeof(struct bmp_image));
       image_hor -> header = calloc(1,sizeof(struct bmp_header));
       
       if(image -> header->type != 19778){
        //printf("jpo2");
        free(image_hor);
        return NULL;
       }
       image_hor -> header->type = image -> header->type;
       image_hor -> header->reserved1 = image -> header->reserved1;
       image_hor -> header->reserved2 = image -> header->reserved2;
        if(image -> header->offset != 54){
         //printf("jpo3");
         free(image_hor);
         return NULL;
       }
       image_hor -> header->offset = image -> header->offset;
       if( image -> header->dib_size != 40){
         //printf("jpo4");
         free(image_hor);
         return NULL;
       }
       image_hor -> header->dib_size = image -> header->dib_size;
       if(image -> header->width <= 0 || image -> header->width > 10000){
         //printf("jpo5");
        free(image_hor);
         return NULL;
       }
       image_hor -> header-> height = image -> header->width;
       if(image -> header->height <= 0 || image -> header->height > 10000){
         //printf("jpo6");
          free(image_hor);
         return NULL;
       }
       image_hor -> header->width = image -> header-> height;
       image_hor -> header->planes = image -> header->planes;
       if(image -> header-> bpp != 1 && image -> header->bpp != 4 && image -> header->bpp != 8 && image -> header->bpp != 24){
         //printf("%d\n",image -> header-> bpp);
          free(image_hor);
         return NULL;
       }
       image_hor -> header->bpp = image -> header->bpp;
       if(image -> header-> compression != 1 && image -> header->compression != 0 && image -> header->compression != 2){
         //printf("%d\n",image -> header-> bpp);
         free(image_hor);
         return NULL;
       }
       image_hor -> header->compression = image -> header->compression;
       image_hor -> header->x_ppm = image -> header->x_ppm;
       image_hor -> header->y_ppm = image -> header->y_ppm;
       image_hor -> header->num_colors = image -> header->num_colors;
       image_hor -> header->important_colors = image -> header->important_colors;

    
       image_hor -> data = calloc((image_hor -> header-> width)*(image_hor -> header -> height) ,sizeof(struct pixel));
       uint32_t height = image -> header->width;
       uint32_t width = image -> header->height;

       uint32_t medz = 0;
       if((width*(image_hor ->header -> bpp /8))%4 != 0){
          medz = 4 - width*(image_hor ->header -> bpp /8)%4;
       }
 
       image_hor ->header -> image_size = height*(width*(image_hor ->header -> bpp/8)+medz);
       image_hor ->header -> size =  image_hor ->header -> image_size + 54;
       for(int i = 0; i < height; i++){
          for(int j = 0; j < width; j++){
            image_hor -> data[((int)width*(i+1) - j -1)].red = image -> data[i + (int)height*j].red;
            image_hor -> data[((int)width*(i+1) - j -1)].green = image -> data[i + (int)height*j].green;
            image_hor -> data[((int)width*(i+1) - j -1)].blue = image -> data[i + (int)height*j].blue;
            //printf("me %d\n",image_hor -> data[-j -1 + (int)(image -> header -> width)*(i+1)].green );

         }
       }
       return image_hor;
    }
return NULL;

}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
  if(image != NULL){

    if( image -> header == NULL || image -> data == NULL){
      return NULL;
    }
    if(start_y < 0 || start_x < 0 || (start_y + height) > image -> header -> height || (start_x +  width) > image -> header -> width){
        return NULL;
    }
       struct bmp_image* image_hor = calloc(1,sizeof(struct bmp_image));
       image_hor -> header = calloc(1,sizeof(struct bmp_header));
       
        if(image -> header->type != 19778){
        free(image_hor);
        //printf("jpo2");
        return NULL;
       }
       image_hor -> header->type = image -> header->type;
       image_hor -> header->reserved1 = image -> header->reserved1;
       image_hor -> header->reserved2 = image -> header->reserved2;
        if(image -> header->offset != 54){
        free(image_hor);
         //printf("jpo3");
         return NULL;
       }
       image_hor -> header->offset = image -> header->offset;
       if( image -> header->dib_size != 40){
         free(image_hor);
         //printf("jpo4");
         return NULL;
       }
       image_hor -> header->dib_size = image -> header->dib_size;

      
       image_hor -> header  -> height = height;
       image_hor -> header  -> width = width;
       
       image_hor -> header->planes = image -> header->planes;
       if(image -> header-> bpp != 1 && image -> header->bpp != 4 && image -> header->bpp != 8 && image -> header->bpp != 24){
         //printf("%d\n",image -> header-> bpp);
         free(image_hor);
         return NULL;
       }
       image_hor -> header->bpp = image -> header->bpp;
       if(image -> header-> compression != 1 && image -> header->compression != 0 && image -> header->compression != 2){
         //printf("%d\n",image -> header-> bpp);
          free(image_hor);
         return NULL;
       }
       image_hor -> header->compression = image -> header->compression;

       image_hor -> header->x_ppm = image -> header->x_ppm;
       image_hor -> header->y_ppm = image -> header->y_ppm;
       image_hor -> header->num_colors = image -> header->num_colors;
       image_hor -> header->important_colors = image -> header->important_colors;


       image_hor -> data = calloc(width*height ,sizeof(struct pixel));
       uint32_t medz = 0;
       if((width*(image_hor ->header -> bpp /8))%4 != 0){
          medz = 4 - width*(image_hor ->header -> bpp /8)%4;
       }

       image_hor ->header -> image_size = height*(width*(image_hor ->header -> bpp/8)+medz);
       image_hor ->header -> size =  image_hor ->header -> image_size + 54;

       uint32_t h = image->header->height;
       uint32_t w = image->header->width; 
        for(uint32_t i = 0; i < height; i++){
          for(uint32_t j = 0; j < width; j++){
           image_hor -> data[i*width + j].red = image -> data[i*width +w*(h-start_y-height) + j + start_x].red;
           image_hor -> data[i*width + j].blue = image -> data[i*width +w*(h-start_y-height) + j + start_x].blue;
           image_hor -> data[i*width + j].green = image -> data[i*width +w*(h-start_y-height) + j + start_x].green;
       }
     }
   return image_hor;
  }
return NULL;
}
//struct bmp_image* scale(const struct bmp_image* image, float factor)
//struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width)
//struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep)


//int main(){
//int main(int argc, char **argv){

// FILE* f =  fopen(argv[1],"r");

  //FILE* f = NULL;
//  struct bmp_image* image = read_bmp(f);
  //printf("%d\n",image ->data ->blue);
//  printf("%d\n",image -> data[1].green);
//  printf("%d\n",image -> data[1].red);
//  printf("%d\n",image -> data[1].blue);

  //printf("%d", write_bmp(f,image));
//  printf("%d\n",flip_horizontally(image) -> data[0].green);
//  printf("%d\n",flip_horizontally(image) -> data[0].red);
//  printf("%d\n",flip_horizontally(image) -> data[0].blue);

//  printf("%d\n",flip_vertically(image) -> data[0].green);
//  printf("%d\n",flip_vertically(image) -> data[0].red);
//  printf("%d\n",flip_vertically(image) -> data[0].blue);

//  printf("%d\n",rotate_right(image) -> data[0].green);
//  printf("%d\n",rotate_right(image) -> data[0].red);
//  printf("%d\n",rotate_right(image) -> data[0].blue);

//  printf("%d\n",rotate_left(image) -> data[0].green);
//  printf("%d\n",rotate_left(image) -> data[0].red);
//  printf("%d\n",rotate_left(image) -> data[0].blue);
    //if(crop(NULL,0,0,1,1) == NULL){
    //   printf("ok");
    //}
//  printf("%d\n",crop(image,0,0,1,1) -> data[0].green);
 // free_bmp_image(image);
//  fclose(f);
// return 0;
//}

