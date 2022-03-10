#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printUsage(const char* programName) {
	printf("usage: %s <width> <height> <density> <steps>\n", programName);
}

void printPBM(int* context, int column, int row, int step){
    
}

int count_live_neighbour_cell(short **a, short row, short col, int r, int c){
    int i, j, count = 0;

    for(i=r-1; i<=r+1; ++i){
        for(j=c-1;j<=c+1;++j){
            if((i==r && j==c) || (i<0 || j<0) || (i>=row || j>=col)){
                continue;
            }
            if(a[i][j]==1){
                ++count;
            }
        }
    }
    return count;
}

void copyArrayToGenTwo(short **genOne, short **genTwo, int width, int height){
    short neighbour_live_cell = 0;
    // update current genOne to the new one and write it into genTwo
    for(int i=0; i<width; ++i){
        for(int j=0;j<height;++j){
            neighbour_live_cell = count_live_neighbour_cell(genOne, width, height, i, j);
            if(genOne[i][j] == 1 && (neighbour_live_cell == 2 || neighbour_live_cell == 3)){
                genTwo[i][j] = 1;
            }
 
            else if(genOne[i][j]==0 && neighbour_live_cell==3){
                genTwo[i][j] = 1;
            }
 
            else{
                genTwo[i][j] = 0;
            }
        }
    }

}

void copyArrayToGenOne(short **genOne, short **genTwo, int width, int height){
    short neighbour_live_cell = 0;
    // update current genTwo to the new one and write it into genOne
    for(int i=0; i<width; ++i){
        for(int j=0;j<height;++j){
            neighbour_live_cell = count_live_neighbour_cell(genOne, width, height, i, j);
            if(genOne[i][j] == 1 && (neighbour_live_cell == 2 || neighbour_live_cell == 3)){
                genTwo[i][j] = 1;
            }
 
            else if(genOne[i][j]==0 && neighbour_live_cell==3){
                genTwo[i][j] = 1;
            }
 
            else{
                genTwo[i][j] = 0;
            }
        }
    }
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
    short** genOne = malloc(sizeof(int[width][height]));
    short** genTwo = malloc(sizeof(int[width][height]));

    // filling the array for the first time
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; ++j){
            genOne[i][j] = (rand() % 100) > (density * 100);
        }
    }

    // 50 Images
    for (int i = 0; i < 25; ++i){
        printPBM();
        copyArrayToGenTwo();
        printPBM();
        copyArrayToGenOne();
    }
    
    // free the arrays again
    free(genOne);
    free(genTwo);

    // exiting the program
	return EXIT_SUCCESS;
}