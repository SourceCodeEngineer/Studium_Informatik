#include <stdio.h>
#include <stdlib.h>

int write_n(const char *src_path, const char *dst_path, int n){
    
    int i = 0;
    char buffer[256];

    if(n > 100 || n < 1) return -1; // ERROR -1 -> n is not wetween 0 and 100!

    FILE *src = fopen(src_path, "r");
    if(src == NULL) return -10; // ERROR -10 -> failed to open source file!

    FILE *dst = fopen(dst_path, "w");
    if(dst == NULL) return -11; // ERROR -11 -> failed to open / create destination file!

    while (fgets(buffer, 256, src) != NULL){
        i++;
        if(n == i){fprintf(dst, "%s", buffer); i = 0;}
    }
    
    fclose(src);
    fclose(dst);
    
    return 0;
}

int main(void){
    return EXIT_SUCCESS;
}
