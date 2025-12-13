#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct pls {
    uint32_t len;
    uint32_t refcount;
#ifdef PS_DEBUG
    uint32_t magic;
#endif
    /* declaration style C99. Pointer to offset 8 of type char, don't know how
     * many bytes. It's only the pointer! */
    char str[];
};

/* Initialize a prefixed length string with the specified
 * string in 'init' of length 'len'.
 *
 * The created string has the following layout:
 *
 * +----+-----------\\\
 * |LLLL|My string here
 * +----+-----------\\\
 *
 * Where L is four unsigned bytes stating the total length of the string.
 * Thus this strings are binary safe: _zero_ bytes are permitted in the middle.
 *
 * Defensively, the string is null terminated to allow printf to not overflow.
 *
 * Returns the pointer to the allocated memory. */
char *ps_create(char *init, int len) {
    struct pls *p = malloc(sizeof(struct pls)+len+1);
    p->len = len;
    p->refcount = 1;
#ifdef PS_DEBUG
    p->magic = 0xDEADBEEF;
#endif
    for (int j = 0; j < len; j++) {
        p->str[j] = init[j]; // We should use memcpy() here.
    }
    p->str[len] = 0;
    return p->str;
}

/* Display the string 's' on the screen */
void ps_print(char *s) {
    struct pls *p = (struct pls*)(s - sizeof(*p));
    for (uint32_t j = 0; j < p->len; j++) {
        putchar(p->str[j]); // or putchar(s[j]);
    }
    printf("\n");
}

#ifdef PS_DEBUG
/* Validate that a PS string looks valid. */
void ps_validate(struct pls *p) {
    if (p->magic != 0xDEADBEEF) {
        printf("INVALID STRING: Aborting\n");
        exit(1);
    }
}
#endif

/* Free a previously created PS string. */
void ps_free(char *s) {
    free(s-sizeof(struct pls));
}

/* Decrement the reference count of the given prefixed string by one.
 * Free the object if the refcount reaches 0. */
void ps_release(char *s) {
    struct pls *p = (struct pls*)(s - sizeof(*p));
#ifdef PS_DEBUG
    ps_validate(p);
#endif
    p->refcount--;
    if (p->refcount == 0) {
        ps_free(s);
    }
}

/* Increment the reference count of the given prefixed string */
void ps_retain(char *s) {
    struct pls *p = (struct pls*)(s - sizeof(*p));
#ifdef PS_DEBUG
    ps_validate(p);
#endif
    p->refcount++;
}

/* Return the length of the given prefixed string. */
uint32_t ps_len(char *s) {
    struct pls *p = (struct pls*)(s - sizeof(*p));
    return p->len;
}


int main(void) {
    char *mystr = ps_create("Hello\000 World", 12);
    ps_print(mystr);
    printf("%s %d\n", mystr, (int)ps_len(mystr));

    char *second_ref_str = mystr;
    ps_retain(mystr);

    ps_release(mystr);
    ps_release(second_ref_str);
    printf("About to release the string a third time...\n");
    ps_release(mystr); // Abort!!
    return 0;
}

