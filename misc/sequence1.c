#include <stdio.h>
#include <stdlib.h>

int compute_sequence(int* seqptr, int n, int x0, int m, int b) {
    // make x0 the first entry in the sequence
    *(seqptr + 0) = x0;

    for(int i = 1; i <= n; i++) {
        *(seqptr + i) = (*(seqptr + (i - 1)) * m) + b;
    }
    
    return 0;
}

int print_sequence(int* seqptr, int n) {
    for (int i = 0; i<n; i++) {
        if( i != (n-1) ) {
            printf("%i,", *(seqptr+i));
        } else {
            printf("%i\n", *(seqptr+i));
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 5) {
        printf("Usage: ./sequence <n> <x0> <m> <b>");
        exit(1);
    }

    char * pEnd;

    // use strtol to cast ints and longs to longs
    int n = atoi( *(argv+1) );
    int x0 = atoi( *(argv+2) );
    int m = atoi( *(argv+3) );
    int b = atoi( *(argv+4) );
    
    printf("%i, %i, %i, %i\n", n, x0, m, b);
    
    // allocate block of memory for sequence
    int* seqptr = calloc(n, sizeof(int));

    if (seqptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    // populate allocated memory
    compute_sequence(seqptr, n, x0, m, b);

    // print the contents of the sequence
    print_sequence(seqptr, n);

    // free allocated memory
    free(seqptr);
    seqptr = NULL;


    return 0;
}