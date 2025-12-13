#include <stdio.h>
#include <string.h>
#include <limits.h>

/* IIIIAAAA
 * 8 bytes
 */
struct foo {
    union {
        int i;
        unsigned char a[4];
    };
};


int main(void) {
    // Direct init...
    // struct foo f = {10, {1, 2, 3, 4}};

    // Or...
    struct foo f;
    f.i = INT_MAX;
    printf("INT_MAX:  %d [%d %d %d %d]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);
    printf("INT_MAX:  %d [%02x %02x %02x %02x]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);

    f.i = INT_MIN;
    printf("INT_MIN: %d [%d %d %d %d]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);
    printf("INT_MIN: %d [%02x %02x %02x %02x]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);

    f.i = -2147483647;
    printf("-1:      %d [%d %d %d %d]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);
    printf("-1:      %d [%02x %02x %02x %02x]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);
    return 0;
}
