#pragma once
#include <stdint.h>
int ppmcodec_write(const char* path,uint32_t width,uint32_t height,uint8_t* buffer);
int ppmcodec_read(const char* path,uint32_t* width,uint32_t* height,uint8_t* buffer);