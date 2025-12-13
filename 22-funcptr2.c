#include <stdio.h>
#include <stdlib.h>

/* 0000111122223333444455556666777788889999 */
int compare_integers(const void *a, const void *b) {
    const int *ap = a;
    const int *bp = b;

    // return *ap - *bp; // Risk of overflow!
    if (ap[0] > bp[0]) return 1;
    else if (ap[0] < bp[0]) return -1;
    else return 0;
}

int main(void) {
    int a[10];
    for (int j = 0; j < 10; j++) {
        a[j] = rand()&15;
    }
    for (int j = 0; j < 10; j++) {
        printf("%d ", a[j]);
    }
    printf("\n");

    qsort(a, 10, sizeof(int), compare_integers);
    for (int j = 0; j < 10; j++) {
        printf("%d ", a[j]);
    }
    printf("\n");

    return 0;
}
