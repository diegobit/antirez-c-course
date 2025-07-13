
#include <stdio.h>
#include <string.h>

/* Wrong! The array decays into a pointer when passed to a function */
// int mystrlen(char thestr[]) {
//     return sizeof(thestr) / sizeof(char);
// }

/* stanrdard implementation */
int mystrlen1(char thestr[]) {
    int i = 0;
    while (thestr[i] != 0) {
        i++;
    }
    return i;
}

/* Low level implementation */
int mystrlen2(char *thestr) {
    char *c = thestr;
    while (*c != '\0') {
        c += sizeof(char);
    }
    return c - thestr;
}

/* Example to try slices */
char second_to_last(char l[]) {
    return l[strlen(l)-2];
}

int main() {
    char s[] = "hello";
    printf("%s\n", s);

    int thelen = sizeof(s) / sizeof(char);
    int mylen1 = mystrlen1(s);
    int mylen2 = mystrlen2(s);
    printf("%d, %d, %d\n", thelen, mylen1, mylen2);

    char stl = second_to_last(s);
    printf("s[-2] = %c\n", stl);
}
