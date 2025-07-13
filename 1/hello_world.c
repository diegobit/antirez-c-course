#include <stdio.h>
#include <string.h>
// Still works! the .h only has the signature, then c linker (?) finds the implementation somewhere
// int printf(const char * restrict format, ...);

int sum(int a, int b) {
    return a + b;
}

/* Wrong! The array decays into a pointer when passed to a function */
// int mystrlen(char thestr[]) {
//     return sizeof(thestr) / sizeof(char);
// }
/* correct implementation */

// int mystrlen(char thestr[]) {
//     int i = 0;
//     while (thestr[i] != 0) {
//         i++;
//     }
//     return i;
// }
//
int mystrlen(char *thestr) {
    char *c = thestr;
    while (*c != '\0') {
        c += sizeof(char);
    }
    return c - thestr;
}

char second_to_last(char l[]) {
    // return l[mystrlen(l)-2];
    return l[strlen(l)-2];
}

int main() {
    char s[] = "hello";
    // printf("%lu\n", sizeof(char));

    int l = mystrlen(s);
    printf("%d\n", l);


    // char s[] = {'h', 'e', 'l', 'l', 'o',0};
    // char s[] = "hello";
    // int thelen = sizeof(s) / sizeof(char);
    //
    // char stl = second_to_last(s);
    // printf("%c\n", stl);
    //
    // int numbers[] = {30, 60};
    // int len = sizeof(numbers) / sizeof(int);
    // printf("%d\n", len);

}
