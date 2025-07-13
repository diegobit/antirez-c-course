#include <stdio.h>

void clear(void) {
    // From `clear | hexdump -C`
    // for ascii table run `man ascii`
    //     escape, VAL, escape, VAL, escape, VAL

    // Using exadecimal escape and human readable values
    // printf("\x1b[3J\x1b[H\x1b[2J");

    // Using all hexadecilam characters
    // printf("\x1b\x1b\x5b\x33\x4a\x1b\x5b\x48\x1b\x5b\x32\x4a");

    // Using octal escape and human readable
    printf("\033[3J\033[H\033[2J");

}

int main(void) {
    clear();
    printf("Hello World!\n");

}
