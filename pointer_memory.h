#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct{
    size_t size; 
    void* data;
    char name[128];
    bool ismemory_allocated;
}pointer_void;

pointer_void make_pointer_void(const char* name);
int allocated_pointer_void(pointer_void* pointer,size_t size_alloc);
void free_pointer_void(pointer_void* pointer);
