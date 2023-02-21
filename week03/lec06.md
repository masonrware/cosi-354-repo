# Arrays

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

*no overloading in c*

# C structures

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

We have two namespaces for struct and typedef. The first type is the local namespace and the second is global namespace. 

Global enables all other files to use the defined struct.

Example of a struct that represents a date:

```c
struct Date today;

today.mon = 2;
today.day = 9;
today.year = 2023;

// equivalent to:
Date today = {2, 9, 2023};
```

- A structre's data members are uninitialized by default.
- A structure's identifier used as a souce operand reads the entire struct
- A structure's identifier used as a destination operand writes entire struct

```c
struct Date tomorrow;
tomorrow = today;
// All the month day and year get copied over
```

## Nesting Structures

```c
typedef struct { /* ... */ } Date;

typedef struct {
    char name[12];
    char type[12];
    float weight;

    Date caught;
} Pokemon;
```

structures can contain other structs and arrays nested as deeply as you wish

## Arrays of structures

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

## Passing Structures

```c
void printDate(Date date) {
    printf("%i/%02i/%i\n", date.mon, date.day, date.year);
}
```

structures are passed-by-value to a function which copies the entire struct.
**THIS IS SLOW**

arrays are passed-by-value to a function but only the starting address is passed - the array elements themselves are not copied.

