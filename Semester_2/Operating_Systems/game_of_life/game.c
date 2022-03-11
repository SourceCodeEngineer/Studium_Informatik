#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printUsage(const char* programName) {
	printf("usage: %s <width> <height> <density> <steps>\n", programName);
}

void printPBM(short arr[], int height, int width){
    FILE* pgmimg;
    pgmimg = fopen("gol_.pbm", "wb");
  
    // Writing the magic number to the file
    fprintf(pgmimg, "P1\n"); 
  
    // Writing width and height
    fprintf(pgmimg, "%d %d\n\n", width, height); 

    for (int i = 0; i < (height * width); i++){
        
        fprintf(pgmimg, "%d ", arr[i]);

        // i + 1 beacsue of indexing
        if (((i+1) % width) == 0){
            fprintf(pgmimg, " \n");
        }
    }

    // closing the file
    fclose(pgmimg);
}

void nextGeneration(counter, arr1, arr2, height, width){
    // if counter uneven, then copy arr1 to arr2 and update cell status

    // if counter even, then copy arr2 to arr1 and update cell status
}

int count_live_neighbour_cell(short array[], short row, short col){

    

    // returns the live neighbors
    return -1;
}

int main(int argc, char* argv[]) {
	if(argc != 5) {
		printUsage(argv[0]);
		return EXIT_FAILURE;
	}

	const int width = atoi(argv[1]);
	const int height = atoi(argv[2]);
	const double density = atof(argv[3]);
	const int steps = atoi(argv[4]);

    if (width < 1 ) {printf("Row count must be greater than zero! You selected %d.\n", width); return -1;}
    if (height < 1 ) {printf("Column count must be greater than zero! You selected %d.\n", height); return -1;}
    
	printf("width:   %4d\n", width);
	printf("height:  %4d\n", height);
	printf("density: %4.0f%%\n", density * 100);
	printf("steps:   %4d\n", steps);

	// Seeding the random number generator so we get a different starting field
	// every time.
	srand(time(NULL));

    // dynamically allocate array
    short* arr1 = malloc(height * width * sizeof(short));
    short* arr2 = malloc(sizeof(short));

    // filling the array for the first time
    for(int i = 0; i < width * height; ++i){
        arr1[i] = (rand() % 100) < (density * 100);
    }
    
    int counter = 1;

    for (int i = 0; i < steps; ++i){
        if(counter % 2 == 1) printPBM(arr1 ,height, width);
        if(counter % 2 == 0) printPBM(arr2 ,height, width);
        
        nextGeneration(counter, arr1, arr2, height, width);
        ++counter;
    }
    
    // free the arrays again
    free(arr1);
    free(arr2);

    // exiting the program
	return EXIT_SUCCESS;
}