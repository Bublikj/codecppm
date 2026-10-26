#include "stdio.h"
#include "stdlib.h"
#include "pointer_memory.h"

pointer_void make_pointer_void(const char* name) {
    pointer_void p = {0};
    if (name) {
        snprintf(p.name, sizeof(p.name), "%s", name);
    }
    return p;
}

int allocated_pointer_void(pointer_void* pointer, size_t size_alloc) {
    if (pointer == NULL) {
        printf("Pointer is NULL for %s\n",pointer->name);
        return 1;
    }

    if (pointer->ismemory_allocated) {
        printf("Memory for %s is already allocated!\n", pointer->name);
        return 1;
    }

    if (size_alloc == 0) {
        printf("Cannot allocate 0 bytes for %s\n", pointer->name);
        return 1;
    }

    void* mem = malloc(size_alloc);
    if (mem == NULL) {
        printf("Allocation for %s in %zu bytes failed!\n",
               pointer->name, size_alloc);
        return 1;
    }

    pointer->data = mem;
    pointer->size = size_alloc;
    pointer->ismemory_allocated = true;

    printf("Allocated %zu bytes for %s successfully\n",
           size_alloc, pointer->name);
    return 0;
}


void free_pointer_void(pointer_void* pointer){
    if (pointer == NULL) return;

    if(pointer->ismemory_allocated){
    
    free(pointer->data);
    
    printf("Free memory for %s in %zu bytes\n",pointer->name,pointer->size);
    pointer->data=NULL;
    pointer->ismemory_allocated=false;
    pointer->size=0;

  }else{
    printf("Memory was free for %s!\n",pointer->name);
  }
}  
