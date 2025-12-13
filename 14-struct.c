#include <stdio.h>
#include <stdlib.h>

struct frac {
    int num;
    int den;
};

/* Create a new fraction, setting num and den as the numerator
 * and denumerator of the fracion.
 * The function returns NULL on out of memory, otherwise the
 * fraction object is returned. */ 
struct frac *create_fraction(int num, int den) {
    struct frac *f = malloc(sizeof(*f));
    if (f == NULL) return NULL; // malloc error checking.
    f->num = num,
    f->den = den;
    return f;
}

/* Simplify the provided fraction */
void simplify_fraction(struct frac *f) {
    for (int d = 2; d <= f->num && d <= f->den; d++) {
        while (f->num % d == 0 &&
               f->den % d == 0)
        {
            f->num /= d;
            f->den /= d;
        }
    }
}

void print_fraction(struct frac *f) {
    printf("%d/%d\n", f->num, f->den);
}

int main(void) {
    // int *f1 = create_fraction(10, 20);
    // int *f2 = create_fraction(3, 4);
    // print_fraction(f1);
    // print_fraction(f2);
    // simplify_fraction(f1);
    // print_fraction(f1);

    // struct frac a;
    // struct fract *b = &a;
    // b->num = 1;
    // b->den = 2;
    // printf("%d %d\n", a->num, a->den);


    struct frac *f1 = create_fraction(10,20);
    struct frac *f2 = create_fraction(3,4);
    print_fraction(f1);
    print_fraction(f2);
    simplify_fraction(f1);
    print_fraction(f1);
}
