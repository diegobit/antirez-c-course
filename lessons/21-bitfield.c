#include <stdio.h>
#include <string.h>
#include <limits.h>

struct foo {
    unsigned char a:4;
    unsigned char b:4;
    unsigned char c:8;
};


int main(void) {
    struct foo f;
    printf("size struct: %zu\n", sizeof(f));
    f.a = 15;
    f.b = 2;
    f.c = 3;
    printf("%d %d %d\n", f.a, f.b, f.c);
    return 0;
}
