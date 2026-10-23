#include "stdio.h"
#include <stdint.h>
#include <string.h>

int ppmcodec_write(const char* path,uint32_t width,uint32_t height,uint8_t* buffer){

    FILE* file=fopen(path, "wb");

    if(file==NULL){
      return 1;
    }

    fprintf(file,"P6\n%d %d\n255\n",width,height);

    fwrite(buffer,sizeof(uint8_t),width*height*3,file);

    fclose(file);
    
    return 0;
}

int ppmcodec_read(const char* path,uint32_t* width,uint32_t* height,uint8_t* buffer){
    FILE* file=fopen(path, "rb");

    if(file==NULL){
      return 1;
    }

    fclose(file);

    return 0;
}
