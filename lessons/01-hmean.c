#include <stdio.h>
#include <stdlib.h>

int main() {
    // int* l = calloc(2, sizeof(int));
    // l[0] = 30;
    // l[1] = 60;
    int numbers[] = {30, 60};
    int len = sizeof(numbers) / sizeof(int);

    // for (int i = 0; i < len; i++) {
    //     printf("%d, ", numbers[i]);
    // }
    // printf("\n");
    //
    // Compute harmonic mean
    float den = 0;
    for (int i = 0; i < len; i++) {
        den += 1.0 / numbers[i];
    }
    float hmean = len / den;
    printf("Harmonic mean: %f\n", hmean);

    return 0;
}
