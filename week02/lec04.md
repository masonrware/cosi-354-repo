# 1d Arrays on The Heap

### Stack vs Heap

**Stack**
static (fixed in size) allocations
allocation size known during compile time

**Heap**
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

# C Strings

- a sequence of char. with null term char `'\0'`
- an ID of char with str length + 1

- a string literal is allocated prior to execution in the CODE segment of memory
  - CODE segment of memory is read only


**Initialization**

```c
void someFunction() {
    char *strp = "CS 354";
}
```

The above pointer is on the stack that points to a string literal stored in the CODE segment of memory.

### Meet string.h