#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void) {
    int fd = open("stdio3.c", O_RDONLY);
    printf("Open file descriptor: %d\n", fd);

    void *mem = mmap(
        NULL,       // mmap will give me the pointer
        100,        // size
        PROT_READ,  // only read
        MAP_FILE|MAP_SHARED, //map_shared to have my writes go to other processes
        fd,
        0           // offset
    );
    printf("File mapped at %p\n", mem);
    printf("%c", ((char*)mem)[0]);

    // write to file through the pointer!
    char *s = mem;
    for (int j = 0; j < 10; j++) {
        printf("s[%d] = %c\n", j, s[j]);
    }

    return 0;
}
