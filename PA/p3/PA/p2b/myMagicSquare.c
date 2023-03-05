///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
// Other Files:
// Semester:         CS 354 Spring 2023
// Instructor:       Deb Deppeler
//
// Author:           Mason R. Ware
// Email:            mrware@wisc.edu
// CS Login:         mware
// GG#:              GG1
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including family, friencs, classmates, tutors,
//                   Peer Mentors, TAs, and Instructor.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct
{
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/*
 * Helper function defined to populate a square with 0s.
 *
 * int **arr    pointer to array of pointers to arrays
 * int n        dimesnion of the square
 */
void setZero(int **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            *(*(arr + i) + j) = 0;
        }
    }
}

/*
 * Helper function to print out array.
 *
 * int **arr    pointer to array of pointers to arrays
 * int n        dimesnion of the square
 */
void printSquare(int **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%i | ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

/*
 * Helper function that implements the alternate
 * Siamese algorithm.
 *
 * int **arr    pointer to array of pointers to arrays
 * int n        dimesnion of the square
 */
int siameseAlgo(int **arr, int size)
{
    int rownum = size / 2;
    int colnum = size - 1;

    for (int num = 1; num <= size * size;)
    {
        // we have gone off the top right.
        if (rownum == -1 && colnum  == size)
        {
            colnum = size - 2;
            rownum = 0;
        }
        else
        {
            // we have gone off the right side.
            if (colnum == size)
            {
                colnum = 0;
            }
            // we have gone off the top.
            if (rownum < 0)
            {
                rownum = size - 1;
            }
        }
        // if the item is populated.
        if (*(*(arr + rownum) + colnum))
        {
            colnum -= 2;
            rownum++;
            continue;
        }
        else
        {
            *(*(arr + rownum) + colnum) = num++;
        }

        colnum++;
        rownum--;
    }
    return 0;
}

/*
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize()
{
    int size;

    printf("Enter magic square's size (odd integer >=3)\n");
    scanf("%i", &size);
    if ((size % 2) != 1)
    {
        printf("Magic square size must be odd.\n");
        exit(1);
    }
    else if (size < 3)
    {
        printf("Magic square size must be >= 3.\n");
        exit(1);
    }
    return size;
}

/*
 * Makes a magic square of size n using the
 * Siamese magic square algorithm or alternate from assignment
 * or another valid alorithm that produces a magic square.
 *
 * n is the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n)
{

    // allocate the struct on the heap.
    MagicSquare *ms_struct = malloc(sizeof(*ms_struct));

    // populate the members of the struct - generate the pointer
    // component of the 2d array on the heap.
    ms_struct->size = n;
    ms_struct->magic_square = malloc(n * sizeof(int *));

    if (ms_struct->magic_square == NULL)
    {
        printf("Failed to Allocate Memory.\n");
        exit(1);
    }
    // initialize the square with heap arrays.
    for (int i = 0; i < n; i++)
    {
        *(ms_struct->magic_square + i) = (int *)malloc(n * sizeof(int));
        if (*(ms_struct->magic_square + i) == NULL)
        {
            printf("Failed to Allocate Memory.\n");
            exit(1);
        }
    }

    // populate the square with zeros
    setZero(ms_struct->magic_square, n);

    // repopulate the square with the siamese method
    siameseAlgo(ms_struct->magic_square, n);

    return ms_struct;
}

/*
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename)
{
    FILE *fp;

    fp = fopen(filename, "w+");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    // print size on first line
    fprintf(fp, "%i\n", magic_square->size);
    for (int i = 0; i < magic_square->size; i++)
    {
        for (int j = 0; j < magic_square->size; j++)
        {
            if (j != ((magic_square->size) - 1))
            {
                fprintf(fp, "%i, ", *(*(magic_square->magic_square + i) + j));
            }
            else
            {
                fprintf(fp, "%i", *(*(magic_square->magic_square + i) + j));
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/*
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 *
 * <output_filename>    CLA string that is the name
 *                      of the file to be written to.
 */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./myMagicSquare <output_filename>\n");
        exit(1);
    };

    int size = getSize();
    MagicSquare *ms_struct = NULL;

    // Generate the magic square.
    ms_struct = generateMagicSquare(size);

    // debug statement
    // printSquare(ms_struct->magic_square, size);

    fileOutputMagicSquare(ms_struct, *(argv + 1));

    // Free all dynamically allocated memory.
    for (int i = 0; i < size; i++)
    {
        free(*(ms_struct->magic_square + i));
    }
    free(ms_struct->magic_square);
    free(ms_struct);

    return 0;
}

// S23
