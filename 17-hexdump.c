#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
* struct pls {
*    long len;
*    char str[];
};
*/

struct pls {
    long len;
    char str[];
};

/* The difference between the two is that with *str we are allocating a pointer
 * at the end of the structure, while with str[] we are not. In this case we
 * are just having a shortcut to go to the end of the struct. In the first way
 * we have a pointer that goes who knows where (two allocations), while in the
 * second we will allocate right next to the struct
 *
 * p -> +-------------------+
        | len = 6           |   8 bytes
        +-------------------+
        | str  ------------ |---+
        +-------------------+   |
                                v
                        +-------------------+
                        | 'h'               |
                        | 'e'               |
                        | 'l'               |
                        | 'l'               |
                        | 'o'               |
                        | '\0'              |
                        +-------------------+
 *
 * vs:
 * p -> +-------------------+
        | len = 6           |   8 bytes (on 64-bit)
        +-------------------+
        | 'h'               |
        | 'e'               |
        | 'l'               |
        | 'l'               |
        | 'o'               |
        | '\0'              |
        +-------------------+
 *
 *
*/

#define HEXDUMP_CHARS_PER_LINE 8
void hexdump(void *p, size_t len) {
    unsigned char *byte = p;
    size_t po = 0;
    for (size_t j = 0; j < len; j++) {
        printf("%02X ", byte[j]);
        if ((j+1) % HEXDUMP_CHARS_PER_LINE == 0 || j == len-1) {
            if (j == len-1) {
                int pad = HEXDUMP_CHARS_PER_LINE -
                    (len % HEXDUMP_CHARS_PER_LINE);
                pad %= HEXDUMP_CHARS_PER_LINE;
                for (int i = 0; i < pad; i++) printf("~~ ");
            }

            printf("\t");
            for (size_t i = po; i <= j; i++) {
                int c = isprint(byte[i]) ? byte[i] : '.';
                printf("%c", c);
            }
            printf("\n");
            po = j+1;
        }
    }
}

int main(void) {
    struct pls s;
    s.len = 10;
    memset(s.str, 0xFF, sizeof(s.str));
    memcpy(s.str, "1234567890", 11);
    printf("%p\n", &s);
    printf("%p\n", s.str);
    // printf("%d\n", s.str-&s);
    hexdump(&s, sizeof(s)-3);
    return 0;
}
