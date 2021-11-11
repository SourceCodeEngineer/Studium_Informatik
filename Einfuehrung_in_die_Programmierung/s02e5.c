    #include <stdio.h>  
    #include <stdlib.h>  

    int main(void)  
    {   
        int i, j, rows, k;  
        scanf("%d", &rows);   

        printf("height: \n");  
        for (i = 1; i <= rows; i++)   
        {  
            for (j = i; j < rows; j++)   
            {  
                printf("  ");   
            }  
            for (k = 1; k <= i; k++)  
            {  
                printf(" %d", k);   
            }  
            printf ("\n");   
        }  
        return EXIT_SUCCESS;      
    }  
