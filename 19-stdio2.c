#include <stdio.h>
#include <ctype.h>
// for open
#include <fcntl.h>
// for close
#include <unistd.h>
// to have the global variable (threadsafe) with the error number
#include <errno.h>

/* Open and read a file with posix system calls, instead of c stdlib */

/* Hexdump function from 17-hexdump/ */
#define HEXDUMP_CHARS_PER_LINE 16
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
    int fd = open("stdio2.c", O_RDONLY);
    printf("Error number is %d (to check, ENOENT is %D)\n", errno, ENOENT);
    if (fd == -1) {
        // perror knows which error encountered open().
        perror("Unable to open file");
        return 1;
    }

    char buf[32];
    ssize_t nread; // has sign because nread could be -1
    while (1) {
        nread = read(fd, buf, sizeof(buf));
        if (nread == -1) {
            perror("Reading file");
            return 0;
        }
        if (nread == 0) break;
        hexdump(buf, nread);
    }

    close(fd);
    return 0;
}
