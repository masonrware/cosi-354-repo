#include <stdio.h>
#include <stdlib.h>

int compute_sequence(long* seqptr, long n, long x0, long m, long b) {
    // make x0 the first entry in the sequence
    *(seqptr + 0) = x0;

    for(int i = 1; i <= n; i++) {
        *(seqptr + i) = (*(seqptr + (i - 1)) * m) + b;
    }
    
    return 0;
}

int print_sequence(long* seqptr, long n) {
    for (int i = 0; i<n; i++) {
        if( i != (n-1) ) {
            printf("%li,", *(seqptr+i));
        } else {
            printf("%li\n", *(seqptr+i));
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
    long n = strtol( *(argv+1), &pEnd, 10 );
    long x0 = strtol( *(argv+2), &pEnd, 10 );
    long m = strtol( *(argv+3), &pEnd, 10 );
    long b = strtol( *(argv+4), &pEnd, 10 );
    
    // allocate block of memory for sequence
    long* seqptr = calloc(n, sizeof(long));

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