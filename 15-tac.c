#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line {
    char *s;
    struct line *next;
};

int main(int argc, char **argv) {
    // Test to see list of args
    for (int i=0; i<argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }

    // Check whether there's at least one arg
    if (argc != 2) {
        printf("Missing file name\n");
        return 1;
    }

    // open file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File %s doesn't exist\n", argv[1]);
    }

    // read from file and print
    // char buf[1024];
    // while (fgets(buf, sizeof(buf), fp) != NULL) {
    //     printf("%s", buf);
    // }

    // read reversed
    char buf[1024];
    struct line *head = NULL;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        struct line *l = malloc(sizeof(struct line));
        size_t linelen = strlen(buf);
        l->s = malloc(linelen+1);
        // strcpy(l->s, buf);
        // or manually
        for (size_t i=0; i<=linelen; i++) {
            l->s[i] = buf[i];
        }
        l->next = head;
        head = l;
    }
    while (head != NULL) {
        printf("%s", head->s);
        struct line *tmp = head->next;
        free(head);
        head = tmp;
    }

    // close
    fclose(fp);

    return 0;
}
