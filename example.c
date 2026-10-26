#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ppmcodec.h"
#include "pointer_memory.h"

int main(void) {
    pointer_void ptr = make_pointer_void("ImageBufferU8");
    
    if (allocated_pointer_void(&ptr, 64 * 64 * 3) != 0) {
        printf("Allocation failed\n");
        return 1;
    }
    uint8_t* buf = (uint8_t*)ptr.data;

    ppmcodec_write("photo2.ppm", 64, 64, ptr.data);

    free_pointer_void(&ptr);
    
    return 0;
}