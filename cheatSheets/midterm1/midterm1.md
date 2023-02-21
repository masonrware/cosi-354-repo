# Midterm 1 Cheat Sheet
This is a cheat sheet for all information that will be covered on Midterm 1 on Thursday, February 23rd.

### Table of Contents
1. [The C Programming Language](#the-c-programming-language)
   1. [Compiling, Running, Debugging](#compiling-running-debugging)
   2. [C Programming Structure](#c-program-structure)
   3. [C Logical Control Flow](#c-logical-control-flow)
   4. [Variables](#variables)
2. [Pointers in C](#pointers-in-c)
   1. [1D Arrays](#1d-arrays)
   2. [Pointers and 1D Arrays](#pointers-and-1d-arrays)
   3. [Passing Addresses](#passing-addresses)
   4. [1D Arrays on The Heap](#1d-arrays-on-the-heap)
3. [C Strings](#c-strings)
   1. [String.h](#stringh)
4. [Command Line Arguments (CLAs)](#command-line-arguments-clas)
5. [2D Arrays](#2d-arrays)
   1. [2D SAAs](#stack-allocated-2d-arrays)
   2. [Heap vs. Stack](#2d-arrays-on-the-stack-vs-heap)
   3. [Array Caveats](#array-caveats)
6. [Structures](#structures)
   1. [Nesting Structures](#nesting-structures)
   2. [Pointers to Structures](#pointers-to-structures)
7. [Standard I/O](#standard-io-in-c)
   1. [Standard Input](#standard-io)
   2. [String Input](#string-io)
   3. [File I/O](#file-io)
8. [Virtual Memory](#virtual-memory)

* * *

## The C Programming Language
1. #### Compiling, Running, Debugging
- Compiling a C source code file is making an object file (machine code) of the program.

   How to build an executable of a C file:
   ```shell
   $gcc prog1.c
   ```
   OR
   ```shell
   $gcc prog1.c -Wall -m32 -std=gnu99 -o prog1
   ```
   &nbsp;
- Running an executable from the CLI:
   ```shell
   $a.out
   ```

2. #### C Program Structure
- Functions:

   A caller function is a function that starts a new function

   A callee function is the function that is being started

- Functions Sharing Data:
   
   An argument is data passed to a function

   A parameter is a variable that stores info in an argument

   pass-by-value means that when data is provided as an argument, a copy of the data is created as a parameter

   return-by-value eans the compiler copies the return value and sends it to the callee

3. #### C Logical Control Flow
- C Sequencing:
   C's logic is controlled by sequencing. The sequence of an executing function is as follows:

   execution...
   - starts in main function
    - flows from top to bottom
      - one statement and then the next
    - each statement is separated by a `;`
    - `{...}` indicate blocks of code

- C Selection:
   ##### *Which values mean true? :*

   - [ ] true
   - [X] 42
   - [X] -17
   - [ ] 0

   ##### *What is output by this code when `money` is 11, -11, 0*

   ```
   if(money == 0)          printf("you're broke\n");
   else if (money < 0)     printf("you're in debt");
   else                    printf("you've got money\n");
   ```

   - 11: you've got money
   - -11: you're in debt
   - 0: you've got money

   ##### *What is output by this code when the date is 10/31?*

   ```
   if (month == 10) {
       if (day == 31)
           printf("Happy Halloween!\n")
   } else
       printf("It's not october.\n")
   ```

   without braces, the else is called a *dangling else*
   

- C Repition:

   Basic While Loop in C:
   ```c
   int i = 0;
   while (i < 11) {
      printf("%i\n", i);
      i++;
   }
   ```

   Basic For Loop in C:
   ```c
   for (int j = 0; j < 11; j++) {
      printf("%i\n", j);
   }
   ```

   Basic Do-While Loop in C:
   ```c
   int k = 0;
   do {
      printf("%i\n", k);
      k++;
   } while (k < 11);
   ```
   
4. #### Variables
   A scalar variable is a primitive unit of storage.

   - Aspects of a Variable:
      - idenitifier:    name
      - value:          data stored
      - type:           representation of the data
      - address:        starting location of a variable's memory
      - size:           number of bits/bytes

   A scaler variable used as a:
      - source operand:
         `printf("%i\n", i);`
      - destination operand:
         `i = 11;`

   &nbsp;
   - Linear Memory Diagram
   <img src="./img/Screen Shot 2023-02-20 at 4.02.17 PM.png" alt="memory diagram"/>

   - *byte addressablity*: each address identifies 1 byte

   - *endianess*: byte ordering for variables that require consecutive bytes in memory
      - *little endian*: least significant byte in lowest address
      - *big endian*: most significant byte in lowest address

* * *

## Pointers in C

   A Pointer variable is:
   - a scalar variable whose value is a memory address
   - similar to Java references but not the exact same

   Why?
   - for indirect access to memory
   - for indirect access to functions
   - they are common in C libraries
   - for access to MMOI hardware

   &nbsp;
   - dereference a pointer by prepending it with `*`
   - declare a pointer like so:
   ```c
   int *p2;
   ```
   What does the following code do?
   ```c
   int **q = &p1;
   ```

   answer: pointer to a pointer

1. #### 1D Arrays
   An array is a compound unit of storage storing elements of one type

   You access arrays using an identifier and index

   allocated as a contiguous block of fized size memory on the stack

- Declaring and Defining 1D Arrays:
   ```
   int a[5];
   ```

   - This array has 5 integer element addresses
   - This memory was allocated from the stack
   - `a[1] = 11` is the code that assigns 11 to the first index of a

   - linear memory diagram of a:

   a:
   | 0  | 1  | 2 |  3 | 4  |
   |---|---|---|---|---|
   |   |   |  |   |   |

- in C, the identifier for a stack allocated array is not a variable
  - we cannot assign a new array to a

- A SAA identifier used as a source operand:
  - `printf("%p\n", a)`

- A SAA idenitfier used as a destination operand:
  - compiler error! cannot assign a new array to a

2. #### Pointers and 1D Arrays
   `int a[5]`
   initializes a stack allocated array of size five, looks like this:

   a:
   | 0  | 1  | 2 |  3 | 4  |
   |---|---|---|---|---|
   |   |   |  |   |   |

   `a[i] === *(a+i)`

   we can dereference the address associated with (a+1)

   code to create a pointer p having the address of array a above:

   `int *p = a;`

   code to give a[4] 44:

   `*(p+4) = 44;`

3. #### Passing Addresses
   **call stack tracing**:
   - manually tace code with functions in manner that mimics machine
   - each function gets a box or a rectangle
     - this is called the stack frame
   - stack frame stores parameters, local variables, temporary variables, ...
   - the "top box" is the running function
     - those below are waiting for callee return
  
   - pointers: param is a pointer var that gets copy of addr of arg
   - arrays: param is a pointer var that gets a copy of addr to array


   changing a callee's parameter changes the callee's copy, not the caller's argument.

   passing an address requires trust because the callee can change the caller value

4. #### 1D Arrays on The Heap
   **Stack**:

   static (fixed in size) allocations
   allocation size known during compile time

   **Heap**:

   dynamic allocations
   during runtime

   Why use a heap?
   - access to more mem. than available at compile time
   - having blocks of memory that can be allocated freed in arbitrary order during runtime

   Heap functions in C:

   ```c
   void* malloc(size_in_bytes)
   ```

   For reserving a block of heap memory of specified size
   it returns a generic pointer that can be assigned to any pointer type

   ```c
   void free(void* ptr)
   ```

   frees the heap block that the pointer points to

   ```c
   sizeof(operand)
   ```

   returns size in bytes of operand

   Code to allocate an integer array named a having 5 elements (dynamically): 

   ```c
   int *a = malloc(sizeof(int)*5)
   ```

   write the code that uses a pointer named p to give the element at index 3 a value of 33

   ```c
   int *p = a;
   *(p+3) = 33;
   ```

   what is a dangling pointer?

   A pointer variable with address to heap memory that has been freed.

   **Watch out for memory leaks**

   Heap memory can become unusable if not freed properly.

   ```c
   int *p = malloc(sizeof(int)); //one byte
   int *q = malloc(sizeof(int)); //one byte
   ...
   p = q;
   ```

   Don't return addresses of local variables!

   ```c
   int *ex1() {
      int i = 11;
      return &i;
   }
   int *ex2(int size) {
      int a[size];
      return a;
   }
   ```

* * *

## C Strings
  - a sequence of char. with null term char `'\0'`
  - an ID of char with str length + 1

  - a string literal is allocated prior to execution in the CODE segment of memory
    - CODE segment of memory is READ ONLY


  **Initialization**

  ```c
  void someFunction() {
      char *strp = "CS 354";
  }
  ```

  The above pointer is on the stack that points to a string literal stored in the CODE segment of memory.

1. #### String.h
   - `int strlen(const char *str)`
   Returns the length of string str up to but not including the null character.

   - `int strcmp(const char *str1, const char *str2)`
   Compares the string pointed to by str1 to the string pointed to by str2.
   returns: < 0 (a negative) if str1 comes before str2
   0 if str1 is the same as str2
   \> 0 (a positive) if str1 comes after str2
   
   - `char *strcpy(char *dest, const char *src)`
   Copies the string pointed to by src to the memory pointed to by dest
   and terminates with the null character.
   
   - `char *strcat(char *dest, const char *src)`
   Appends the string pointed to by src to the end of the string pointed to by dest
   and terminates with the null character.

* * *
## Command Line Arguments (CLAs)

   ```shell
   $gcc myprog.c -Wall -m32 -std=gnu99 -o myprog
   ```
   command followed by program args

   How to use arguments?

   ```c
   int main(int argc, char *argv[]) {
      for (int i = 0; i < argc; i++) {
         printf("%s\n", argv[i]);
      }
      return 0;
   }
   ```

  - argv is an array of pointers to chars

* * *
## 2D Arrays

make a 2d array pointer named m

```c
int **m;
```

assign m an "array of arrays"

```c
m = malloc(size*sizeof(int *));
if(m==NULL){printf("....");}
```

assign each element in the "array of arrays" its own row of ints.

```c
*(m+n) = malloc(size*sizeof(int));
```

Write the code to free the heap allocated 2d array

```c
for(int i=0; i<size; i++){
    free(*(m+i));
}
free(m); m=NULL;
```

1. #### Stack Allocated 2D Arrays
   ```c
   void someFunction(){
      int m[2][4] = {{0,1,2,3}, {4,5,6,7}};
   }
   ```
   <img src="./img/Screen Shot 2023-02-20 at 5.27.58 PM.png" alt="2D SAA"/>

2. #### 2D Arrays on the Stack vs. Heap
   <img src="./img/Screen Shot 2023-02-20 at 5.29.33 PM.png" alt="2D stack vs. heap"/>

3. #### Array Caveats
   - Arrays have no bounds checking
   - arrays connot be return types!
   ```c
   int[] makeIntArray(int size) {
       return malloc(sizeof(int) * size);
   }
   ```
   replace `int[]` with `int *`

   - Not all 2d arrays are alike
     - what is the layout for all 2d arryas on the stack?
       - 2d arrays on the stack are all contiguous fixed blocks in row major order
     - what is the layout for 2d arrays on the heap?
       - array of arrays, pointer to pointers to arrays on the heap.
           - to make a heap array point to a contiguous block of memory, you just 1d it and make the pointers in your first array point to the first element of each row


   - stack allocated arrays require all but their first dimension to be specified
   Why? because the compiler only needs # of columns to compute element address

* * *
## Structures

   structs are:
   - user defined types
   - a compound unit of storage with data member of diff types
   - access using identifier and data member name
   - allocated as contiguous fixed-size block of memory

   How to define:

   ```c
   // Way one:
   struct <typename> {
      <data-member-declarants>;
   };

   // Way two:
   typedef struct {
      <data-member-declarants>
   } <typename>;
   ```
   **Note the semi colon placements!!!**

   - A structre's data members are uninitialized by default
   - A structure's identifier used as a souce operand reads the entire struct
   - A structure's identifier used as a destination operand writes entire struct

1. #### Nesting Structures

  ```c
  typedef struct { /* ... */ } Date;

  typedef struct {
      char name[12];
      char type[12];
      float weight;

      Date caught;
  } Pokemon;
  ```

  structures can contain other structs and arrays nested as deeply as you wish.

- Arrays of structs:
   
   &nbsp;
    arrays can have structs as elements

    ```c
    Pokemon pokedex[2] = {
        {"Abra", "psychic", 43.0, {
            2, 21, 2021
        }},
        {"Oddish". "grass", 22.9, {
            9, 22, 2022
        }}
    };
    ```

    Change the weight of the pokemon at index 1 to 22.2.

    ```c
    pokedex[1].weight = 22.2;
    ```

    Change the month to 11 of the pokemon at index 0.

    ```c
    pokedex[0].caught.mon = 11;
    ```

- Passing Strucutres

   &nbsp;
   ```c
   void printDate(Date date) {
      printf("%i/%02i/%i\n", date.mon, date.day, date.year);
   }
   ```

   structures are passed-by-value to a function which copies the entire struct.
   **THIS IS SLOW**

   arrays are passed-by-value to a function but only the starting address is passed - the array elements themselves are not copied.

2. #### Pointers to Structures 
   Why use pointers to structs?
   - to avoid copying overhead of pass-by-value
   - allows functions to manipulate the larger-scoped struct
   - enables heap allocation of structs
     
   Declare a pointer to a pokemon and dynamically allocate its structure.

   ```c
   Pokemon * pmptr;
   pmptr = malloc(sizeof(Pokemon));
   ```

   Assign a weight to the pokemon

   ```c
   *(pmptr).weight=43;
   ```

   Deallocate the Pokemon's memory
   ```c
   free(pmptr); //correct
   ```

* * *
## Standard I/O in C

1. #### Standard I/O
- Standard Input
   
   ```c
   getchar(); //reads 1 char
   gets();    //reads 1 string ending with a newline char, BUFFER MIGHT OVERFLOW
   ```

   ```c
   int scanf(const char *format_string, &v1, &v2, ...) {}
   ```
   reads formatted input from the console keyboard.

- Standard Output

   ```c
   putchar(); //writes 1 char
   puts();    //writes 1 string
   ```

   ```c
   int printf(const char *format_string, v1, v2, ...) {}
   ```
   writes formatted output to the console terminal window.

2. #### String I/O
- String Input

   string scan scans a string given a format and saves those values in the specified variables.
   ```c
   int sscanf(const char *str, const char *format_string, &v1, &v2, ...) {}
   ```

   string print prints the formatted string copy into the provided string, not to the console.
   ```c
   int sprintf(char *str, const char *format_string, v1, v2, ...) {}
   ```

3. #### File I/O
- File Input

   ```c
   fgetc   //reads 1 char at a time
   fgets   //reads 1 string terminated with a newline char or EOF
   ```

   ```c
   int fscanf(FILE *stream, const char *format_string, &v1, &v2, ...) {}
   ```
   reads formatted input from provided file stream.

- File Output
   
   ```c
   int fprintf(FILE *stream, const char *format_string, v1, v2, ...) {}
   ```
   need to worry about overflow - this is printed to a file.


   **Predeined file pointers**

   - `stdin` is console keyboard
   - `stdout` is console terminal window
   - `stderr` is console terminal window, second stream for erros


   ```c
   printf("Hello\n"); === fprintf(stdout, "hello\n");
   ```

   There is no way of reading from one file and writing to another in c.

   In order to do this, we must build a buffer.

   ```c
   const int bufsize = 257;
   char buffer[bufsize];
   ```

- Opening and Closing Files

   ```c
   FILE *fopen(const char *filename, const char *mode)
   ```
   opens the specified `filename` in the specified `mode`.

   ```c
   int fclose(FILE *stream)
   ```
   flushes the output buffer and then closes the specified `stream`.

* * * 
## Virtual Memory
1. #### Three Faces of Memory
- **Process View = Virtual Memory**

   Goal: provide a simple view

   virtual address space (VAS)
   illusion by OS so that each process has its own contiguous block memory.

   The compiler treats this as all the memory you need for your processs.

   But still needs to be partitioned into:
   - Kernel 
     - memory resident portion of the OS
   - Stack
     - grows from bottom to top
     - used for funtion calls 
   - Heap
     - Dynamic memory allocations
   - Data
   - Code
     - Reserved (not accessible)
     - responsible for segfaults

   <img src="./img/Screen Shot 2023-02-21 at 5.23.24 PM.png" alt="simple stack and heap"/>

- **System View = Illusionist (CS 537)**

   Goal: make memory shareable and secure

   in process view, all of memory is ours, but the OS needs to create this illusion. It needs to figure out how to share memory between processes.

   We do this with:

   *pages* which are 4k byte units of memory blocks managed by the OS

   maintains a data structure called the:
   *page table* that maps virtual pages (process view) to physical pages (what it actually has)

   OS will say "you need this spot out of your virtual page?, ok I'll save it in the page table and cache it in secondary storage or main memory".

- **Hardware View = Physical Memory**

   