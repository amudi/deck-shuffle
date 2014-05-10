#include <stdio.h>  // for io
#include <stdlib.h> // for calloc and realloc
#include <string.h> // for memcmp

#ifndef DEBUG
// #define DEBUG
#endif

int *createdeck(int n);
void oneround(int *deck, int n);
int shuffle(int *deck, int n);
int equaldeck(int *a, int *b, int n);

#ifdef DEBUG
void printarray(int *arr, int n)
{
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
#endif

int main(int argc, char **argv) {
    char *arg;
    int *deck;
    int decksize;
    int count;

    if (argc < 2) {
        printf("usage: shuffle <count>\n\ncount is size of deck (positive integer)\n");
        return -1;
    }

    arg = argv[1];
    decksize = strtol(arg, NULL, 10);
    if (decksize < 1) {
        printf("usage: shuffle <count>\n\ncount is size of deck (positive integer)\n");
        return -1;
    }
    deck = createdeck(decksize);
    count = shuffle(deck, decksize);
    printf("%d\n", count);

    free(deck);
    return 0;
}

int *createdeck(int n) {
    int i;
    int *result = malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) {
        result[i] = i + 1;
    }
    return result;
}

void oneround(int *deck, int n) {
    int i;
    int first, second, endofdeck;
    int *workingarray, workingarraysize;
    int *table, endoftable;

    // create working array, copy deck into it;
    workingarraysize = 2 * n - 1;   // just enough
    workingarray = malloc(workingarraysize * sizeof(int));
    for (i = 0; i < n; ++i) {
        workingarray[i] = deck[i];
    }
    i = 0;

    // table as result
    table = malloc(n * sizeof(int));
    endoftable = n - 1;
    endofdeck = n;

    do {

#ifdef DEBUG
        printf("array:"); printarray(workingarray, workingarraysize);
        printf("table:"); printarray(table, n);
        printf("endoftable:%d, endofdeck:%d\n", endoftable, endofdeck);
#endif

        first = workingarray[i];
        second = workingarray[i + 1];
        
        // put first item to the table
        table[endoftable] = first;
        --endoftable;

        // put second item to end of deck
        workingarray[endofdeck] = second;
        ++endofdeck;

        workingarray[i] = 0;
        workingarray[i + 1] = 0;
        i += 2;

    } while (endoftable >= 0);

#ifdef DEBUG
    printf("done, table:"); printarray(table, n);
#endif

    for (i = 0; i < n; ++i) {
        deck[i] = table[i];
    }
    
    free(workingarray);
    free(table);
}

int shuffle(int *deck, int n) {
    int count = 0;
    int i;

    // create reference array
    int *ref = malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) {
        ref[i] = deck[i];
    }

    do {
        oneround(deck, n);
        ++count;

#ifdef DEBUG
        printf("deck: "); printarray(deck, n);
        printf("ref: "); printarray(ref, n);
#endif

    } while (equaldeck(deck, ref, n) != 0);
    free(ref);
    return count;
}

int equaldeck(int *a, int *b, int n) {
    int i;
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            return -1;
        }
    }
    return 0;
}
