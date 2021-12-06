#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int cmp(int x, int y) {
    if (x < y) {
        return 1;
    } else if (x > y) {
        return 0;
    } else {
        return -1;
    }
}

void bubblesort(int a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n; j >= i; j--) {
            if (cmp(a[j], a[j - 1]) < 0)
                swap(&a[j], &a[j - 1]);
        }
    }
}

int main(void) {
    int a[] = {5, 10, 11, 9, 7, 8, 4, 5, 7, 2, 45, 1, 4, 20};
    int n = sizeof(a) / sizeof(*a);
    bubblesort(a, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
