#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printUsage(const char *programName)
{
    printf("usage: %s <width> <height> <density> <steps>\n", programName);
}
void reverseArray(short array[], int width, int height)
{
    for (int i = 0; i < (width * height); ++i)
    {
        if (array[i] == 1)
        {
            array[i] = 0;
        }
        else
        {
            array[i] = 1;
        }
    }
}

int countLiveNeighborCells(short array[], short width, short height, int position)
{
    int i = position;
    int count = 0;
    if (i == 0)
    {
        // logic for upper left corner
        // 3 neighbors
        count += array[i + 1] + array[i + width] + array[i + width + 1];
        return count;
    }
    else if (i == width - 1)
    {
        // logic for upper right corner
        // 3 neighbors
        count = array[i - 1] + array[i + height] + array[i + height - 1];
        return count;
    }
    else if (i == ((width * height) - 1))
    {
        // logic for lower right corner
        // 3 neighbors
        count = array[i - 1] + array[i - height] + array[i - height - 1];
        return count;
    }
    else if (i == ((width * height) - (width)))
    {
        // logic for lower left corner
        // 3 neighbors
        count = array[i + 1] + array[i - height] + array[i - height + 1];
        return count;
    }
    else if (i < width - 1 && i > 0)
    {
        // logic for the first row
        // 5 neighbors
        count = array[i + 1] + array[i - 1] + array[i + width] + array[i + width + 1] + array[i + width - 1];
        return count;
    }
    else if (i < ((height * width) - 1) && i > ((height * width) - (width)))
    {
        // logic for lower row
        // 5 neighbors
        count = array[i + 1] + array[i - 1] + array[i - width] + array[i - width + 1] + array[i - width - 1];
        return count;
    }
    else if ((i > 0) && ((i % (width)) == 0) && i < ((height * width) - (width - 1)))
    {
        // logic for the left column
        // 5 neighbors
        count = array[i + 1] + array[i - width] + array[i - width + 1] + array[i + width] + array[i + width + 1];
        return count;
    }
    else if (i > width + 1 && i < height * width - 2 && (i + 1) % width == 0)
    {
        // logic for right column
        // 5 neighbors
        count = array[i - 1] + array[i - width] + array[i - width - 1] + array[i + width] + array[i + width - 1];
        return count;
    }
    else
    {
        // otherwise it has 8 neighbors, yay
        count = array[i + 1] + array[i - 1] + array[i - width] + array[i + width] + array[i - width - 1] + array[i + width + 1] + array[i - width + 1] + array[i + width - 1];
        return count;
    }
}

void printPBM(short arr[], int height, int width, int variable)
{
    FILE *pgmimg;
    char filename[15];
    snprintf(filename, 14, "gol_%05d.pbm", variable);
    pgmimg = fopen(filename, "wb");

    // Writing the magic number to the file
    fprintf(pgmimg, "P1\n");

    // Writing width and height
    fprintf(pgmimg, "%d %d\n\n", width, height);

    for (int i = 0; i < (height * width); i++)
    {

        fprintf(pgmimg, "%d ", arr[i]);

        // i + 1 beacsue of indexing
        if (((i + 1) % width) == 0)
        {
            fprintf(pgmimg, "\n");
        }
    }

    // closing the file
    fclose(pgmimg);
}

void nextGeneration(int counter, short arr1[], short arr2[], int height, int width)
{
    // if counter uneven, then copy arr1 to arr2 and update cell status
    if (counter % 2 == 1)
    {
        for (int i = 0; i < height * width; ++i)
        {
            // update cell status
            int neighborcell = countLiveNeighborCells(arr1, width, height, i);
            if (neighborcell == 3)
            {
                arr2[i] = 1;
                continue;
            }
            if (neighborcell != 2)
            {
                arr2[i] = 0;
                continue;
            }
            if (neighborcell == 2)
            {
                arr2[i] = arr1[i];
            }
        }
    }
    // if counter even, then copy arr2 to arr1 and update cell status
    if (counter % 2 == 0)
    {
        for (int i = 0; i < height * width; ++i)
        {
            // update cell status
            int neighborcell = countLiveNeighborCells(arr2, width, height, i);
            if (neighborcell == 3)
            {
                arr1[i] = 1;
                continue;
            }
            if (neighborcell != 2)
            {
                arr1[i] = 0;
                continue;
            }
            if (neighborcell == 2)
            {
                arr1[i] = arr2[i];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const int width = atoi(argv[1]);
    const int height = atoi(argv[2]);
    const double density = atof(argv[3]);
    const int steps = atoi(argv[4]);

    if (width < 1)
    {
        printf("Row count must be greater than zero! You selected %d.\n", width);
        return -1;
    }
    if (height < 1)
    {
        printf("Column count must be greater than zero! You selected %d.\n", height);
        return -1;
    }

    printf("width:   %4d\n", width);
    printf("height:  %4d\n", height);
    printf("density: %4.0f%%\n", density * 100);
    printf("steps:   %4d\n", steps);

    // Seeding the random number generator so we get a different starting field
    // every time.
    srand(time(NULL));

    // dynamically allocate array
    short *arr1 = malloc(height * width * sizeof(short));
    short *arr2 = malloc(height * width * sizeof(short));

    // filling the array for the first time
    for (int i = 0; i < width * height; ++i)
    {
        arr1[i] = (rand() % 100) < (density * 100);
    }

    int counter = 1;

    for (int i = 0; i <= steps; ++i)
    {

        if (counter % 2 == 1)
        {
            reverseArray(arr1, width, height);
            printPBM(arr1, height, width, i);
            reverseArray(arr1, width, height);
        }
        else
        {
            reverseArray(arr2, width, height);
            printPBM(arr2, height, width, i);
            reverseArray(arr2, width, height);
        }
        nextGeneration(counter, arr1, arr2, height, width);
        ++counter;
    }
    // free the arrays again
    free(arr1);
    free(arr2);

    // exiting the program
    return EXIT_SUCCESS;
}
