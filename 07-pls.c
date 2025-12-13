#include <stdio.h>
#include <stdlib.h>

/* Initialize a prefixed length string with the specified
 * string in 'init' of length 'len'.
 *
 * Warning: this function does not check for buffer overflows. */
void ps_init(char *s, char *init, int len) {
    unsigned char *lenptr = (unsigned char*)s;
    *lenptr = len;
    for (int j = 0; j < len; j++) {
        s[j+1] = init[j];
    }
}

/* Display the string 's' on the screen */
void ps_print(char *s) {
    unsigned char len = (unsigned char)*s;
    for (int j = 1; j < len+1; j++) {
        putchar(s[j]);
    }
    printf("\n");
}

/* Initialize a prefixed length string with the specified
 * string in 'init' of length 'len'.
 *
 * The created string has the following layout:
 *
 * +-+----------\\\
 * |L|My string here
 * +-+----------\\\
 *
 * Where L is one unsigned byte stating the total length of the string.
 * Thus this strings are binary safe: _zero_ bytes are permitted in the middle.
 *
 * Defensively, the string is null terminated to allow printf to not overflow.
 *
 * Returns the pointer to the allocated memory. */
char *ps_create(char *init, int len) {
    char *s = malloc(1+len+1);
    *s = (unsigned char)len;
    for (int j = 0; j < len; j++) {
        s[j+1] = init[j];
    }
    s[len+1] = 0;
    return s;
}

/* Return the pointer to the null terminated C string embedded
 * inside our PS string 's'. */
char *ps_getc(char *s) {
    return s+1;
}

int main(void) {
    // Example without malloc
    char buf[256];
    ps_init(buf, "Hello\000 World", 12);
    ps_print(buf);

    // Example with malloc
    char *mystr = ps_create("Hello\000 World", 12);
    ps_print(mystr);

    char *cstr = ps_getc(mystr);
    printf("%s\n", cstr); // will print only "Hello"

    free(mystr);
    return 0;
}
