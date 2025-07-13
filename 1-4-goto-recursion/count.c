#include <stdio.h>

void count_rec(int start, int end) {
    if (start > end) {
        printf("\n");
        return;
    }
    printf("%d ", start);
    count_rec(start+1, end);
}

void count_goto(int start, int end) {
iterate:
    if (start > end) {
        printf("\n");
        return;
    }
    printf("%d ", start);
    start++;
    goto iterate;
}

void count_while(int start, int end) {
    int i = start;
    while (i <= end) {
        printf("%d ", i);
        i++;
    }
    printf("\n");
}

void count_for(int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

int main(void) {
    printf("rec   ");
    count_rec(0, 9);
    printf("\ngoto  ");
    count_goto(0, 9);
    printf("\nwhile ");
    count_while(0, 9);
    printf("\nfor   ");
    count_for(0, 9);
}
