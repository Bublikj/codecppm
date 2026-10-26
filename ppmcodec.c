#include "stdio.h"
#include <stdint.h>
#include <string.h>
#include "stdlib.h"

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
    FILE* file = fopen(path, "rb");

    if (file == NULL) {
        *width = 0;
        *height = 0;
        return 1; // Ошибка открытия файла
    }

    // 1. Чтение и проверка заголовка
    char line[256];
    
    // Чтение P6
    if (fgets(line, sizeof(line), file) == NULL || strncasecmp(line, "P6\n", 3) != 0) {
        fclose(file);
        *width = 0;
        *height = 0;
        return 1; // Ошибка формата (не P6)
    }

    // Чтение Width Height
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        *width = 0;
        *height = 0;
        return 1; // Ошибка чтения размеров
    }
    
    // Парсинг ширины и высоты
    int w_temp, h_temp, max_val;
    if (sscanf(line, "%d %d", &w_temp, &h_temp) != 2) {
        fclose(file);
        *width = 0;
        *height = 0;
        return 1; // Ошибка парсинга размеров
    }

    // Чтение MaxValue
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        *width = 0;
        *height = 0;
        return 1; // Ошибка чтения MaxValue
    }
    
    // Парсинг максимального значения
    if (sscanf(line, "%d", &max_val) != 1 || max_val != 255) {
        fclose(file);
        *width = 0;
        *height = 0;
        return 1; // Ошибка формата (не 255)
    }

    // 2. Проверка буфера и чтение данных
    size_t required_size = (size_t)(*width) * (*height) * 3;
    
    if (buffer == NULL || required_size > 0) { 
        // Проверка, что буфер не NULL и что мы ожидаем данные
        // Примечание: В реальности, если буфер нулевой, мы должны вернуть ошибку,
        // но для целей этого примера, мы предполагаем, что caller предоставил правильный буфер.
        printf("memory allocated");
        buffer=malloc(required_size);
    }
    
    size_t bytes_read = fread(buffer, 1, required_size, file);
    
    fclose(file);

    if (bytes_read != required_size) {
        // Ошибка при чтении всего блока данных
        *width = 0;
        *height = 0;
        return 1; 
    }

    *width = (uint32_t)w_temp;
    *height = (uint32_t)h_temp;
    return 0; // Успех
}