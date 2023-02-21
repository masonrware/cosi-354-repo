# Pointers to Structs

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

# Standard and String I/O in stdio.h

## Standard I/O

### Standard Input
Standard input
```c
getchar //reads 1 char
gets    //reads 1 string ending with a newline char, BUFFER MIGHT OVERFLOW
```

```c
int scanf(const char *format_string, &v1, &v2, ...) {}
```

### Standard Output
```c
putchar //writes 1 char
puts    //writes 1 string
```

```c
int printf(const char *format_string, v1, v2, ...) {}
```

## String I/O

### String Input

string scan scans a string given a format and saves those values in the specified variables.
```c
int sscanf(const char *str, const char *format_string, &v1, &v2, ...) {}
```

string print prints the formatted string copy into the provided string, not to the console.
```c
int sprintf(char *str, const char *format_string, v1, v2, ...) {}
```

## File I/O

### File Input

```c
fgetc   //reads 1 char at a time
fgets   //reads 1 string terminated with a newline char or EOF
```

```c
int fscanf(FILE *stream, const char *format_string, &v1, &v2, ...) {}
```
reads formatted input from provided file stream.


### File Output

```c
int fprintf(FILE *stream, const char *format_string, v1, v2, ...) {}
```
need to worry about overflow - this is printed to a file.


## Predeined file pointers

`stdin` is console keyboard
`stdout` is console terminal window
`stderr` is console terminal window, second stream for erros

```c
printf("Hello\n"); === fprintf(stdout, "hello\n");
```

There is no way of reading from one file and writing to another in c.

In order to do this, we must build a buffer.

```c
const int bufsize = 257;
char buffer[bufsize];
```