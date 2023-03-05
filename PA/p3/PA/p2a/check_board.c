//////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      boardN.txt, boardNsolution.txt
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

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
	char *line1 = NULL;
	size_t len = 0;

	if ( getline(&line1, &len, fptr) == -1 ) {
		printf("Error reading the input file.\n");
		free(line1);
		exit(1);
	}

	char *size_chars = NULL;
	size_chars = strtok(line1, DELIM);
	*size = atoi(size_chars);

	// free memory allocated for reading first link of file
	free(line1);
	line1 = NULL;
}



/*
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {
	// Iterate through the diagonal elements of the board.
	for (int i = 0; i < size; i++) {
		// Get the diagonal element.
		int *diag = (*(board+i) + i);
		// Iterate across the column and row of the diagonal element.
		for (int j = 0; j < size; j++) {
			// Get the current row target and the current
			// column target. These are what will be compared
			// against every iteration.
			// Row current target is obtained by going to the
			// beginning of the row the diagonal is in and
			// iterating through it.
			// Col current target is obtained by iterating
			// through the rows of the board and offsetting by i.
			int *rowcurr = ((diag-i) + j);
			int *colcurr = (*(board+j) + i);
			// Iterate once more across the column and row of the
			// diagonal element to compare all elements to the current.
			for (int k = 0; k < size; k++) {
				if (j!=k) {
					// Compare the row target to every other element in its row.
					if (*rowcurr != 0 && *rowcurr == *((rowcurr-j)+k)) {
						printf("invalid\n");
						exit(1);
					}
					// Compare the column target to every other element in its column. 
					if (*colcurr != 0 && *colcurr == *(*(board+k)+i)) {
						printf("invalid\n");
						exit(1);
					}
				}
			}
		}
	}
	return 0;   
}    

/*
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA is required, which is the name of the file 
 * that contains board data is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Only exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {              	
	// Check if number of command-line arguments is correct.
	if(argc != 2){
		printf("Usage: ./check_board <input_filename>\n");
		exit(1);
	};

	// Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Can't open file for reading.\n");
		exit(1);
	}

	// Declare local variables.
	int size;

	// Call get_board_size to read first line of file as the board size.
	get_board_size(fp, &size);

	// Check size is legal
	if (size <= 0 || size > 9) {
		printf("invalid\n");
		exit(1);
	}

	// Dynamically allocate a 2D array for given board size.
	int **arr = malloc(size*sizeof(int *));

	if (arr == NULL) {
		printf("invalid.\n");
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		*(arr+i) = malloc(size*sizeof(int));
		if (*(arr+i) == NULL) {
			printf("invalid.\n");
			exit(1);
		}
	}

	// Read the rest of the file line by line.
	// Tokenize each line wrt the delimiter character 
	// and store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < size; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading line %i of the file.\n", i+2);
			free(line);
			exit(1);
		}

		token = strtok(line, DELIM);
		for (int j = 0; j < size; j++) {
			// initialize your 2D array.
			*(*(arr+i) + j) = atoi(token);
			token = strtok(NULL, DELIM);
		}

		free(line);
		line = NULL;
	}
		
	// Call the function valid_board and print the appropriate
	// output depending on the function's return value.
	valid_board(arr, size);
	printf("valid\n");

	// Free all dynamically allocated memory.
	for (int i = 0; i < size; i++) {
		free(*(arr+i));
	}	
	free(arr);

	//Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file.\n");
		exit(1);
	} 

	return 0;       
}       

