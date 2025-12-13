#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

/* Like printf to test variadic functions */
void foo1(char *fmt, ...) {
    va_list ap; /* contains state of arguments to extract */
    va_start(ap, fmt);

    char *p = fmt;
    while(*p) {
        if (*p == 'i') {
            int i = va_arg(ap, int);
            printf("%d\n", i);
        } else if (*p == 's') {
            char *s = va_arg(ap, char*);
            printf("%s\n", s);
        } else {
            printf("Wrong specifier\n");
            goto cleanup;
        }
        p++;
    }

cleanup:
    printf("-- doing cleanup.\n");
    va_end(ap);
}

/* Can we nest variadic functions? Let's try with vprintf */
void foo2(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    char mybuf[32];
    vsnprintf(mybuf, sizeof(mybuf), fmt, ap);

    // example to do padding
    size_t len = strlen(mybuf);
    size_t padding = (80 - len)/2;
    for (size_t j = 0; j < padding; j++) printf(" ");

    // example to do lowercase
    // for (int j = 0; j < sizeof(mybuf); j++) {
    //     mybuf[j] = tolower(mybuf[j]);
    // }

    printf("%s\n", mybuf);

    va_end(ap);
}

int main() {
    printf("Hello world\n");

    // foo1("iisi", 10, 20, "ciao ciao", 5);
    foo2("PROVA %d %d %s %d", 10, 20, "CIAO CIAO", 5);

    return 0;
}

/* Highlights:
 * - Variadic functions in completely dynamic, va_arg extracts the bytes
 *   according to the type specifier I passed... so if that is wrong, who knows
 *   what gets extracted. Antirez says some compilers have specific behavious
 *   to produce warnings. Still it's not c standard to do it.
 * - 
*/

