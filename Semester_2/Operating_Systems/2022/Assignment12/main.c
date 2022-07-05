#include <stdio.h>
#include <stdlib.h>


int main(void){
    FILE *fpr = fopen("datei.txt", "r");
    char content[] = "text\0";
    if (fputs(content, fpr) == EOF){
        printf("FBSchreiben");
        return 0;
    }
    if (fclose(fpr) != 0){
        printf("FBSchließen");
        return 0;
    }
    printf("EB");
    return 0;
}