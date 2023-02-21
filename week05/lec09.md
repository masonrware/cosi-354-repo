# Linux: Processes and Address Space

## Processes

#### Process and Job Control

- Linux is: a multitasking OS which runs multiple processes concurrently
  
`ps` is a snapshot of the running processes on a system

`jobs` lists only processes belonging to the user

`&` runs a process in the background

`ctrl+z` suspends a running process

`bg` backgorund

`fg` foreground

`ctrl+c` stop a running process

#### Program Size

`size <executable or object file>`

#### Virtual Address Space Maps

- Linux enables to see the virtual address space and a map of each process

`$pmap <pid_of_processs>`

`$cat /proc/<pid_of_process>/maps`

`$cat /proc/self/maps/`


#### posix brk & unistd.h

`unistd.h` is a library collection of Posix API functions.

Posix API(Portable OS Interface) is the standard for maintiaing compatibility among Unix OS's.

#### DIY Heap via Posix Calls

`brk` is a program break which is a pointer to the end of the program, at the top of the heap.

```c
int brk(void *addr)
```
sets the top of the heap to the specified address addr.

```c
void *sbrk(intptr t incr)
```
we can increase or decrease the brk point this way.

`errno` is set by OS functions to communicate a specific error

must include:
```c
#include <error.h>

printf("Error: %s\n", strerr(errno));
```
#### C's Heap Allocator & `stdlib.h`

`stdlib.h` contains 25 functions that are commonly used in C.

**C's Heap Allocator Functions**

`void *malloc(size_t size)`
Allocates a generic pointer to block of heap memory of size bytes

`void *calloc(size_t nItems, size_t size)`
allocates, clears to 0, and returns a block of heap memory of nItems * size bytes

`void *realloc(void *ptr, size_t size)`
reallocates to size bytes a previously allocated block of heap memory pointed to by ptr

`void free(void *ptr)`
frees the heap memory pointed to by ptr.

## Meet the Heap

The heap is a segment of a process' virtual address space used for dynamically allocated memory.

can also be thought of as a collection of various sized memory blocks that are managed by an allocator.

A:
- block is a contiguous chunk of memory that contains:
- payload is the part requested and available to the user
- overhead is the additional amount of (nonaccessible) memory requested from the OS. Used by allocator to manage blocks.
- allocator is code that alloc's and frees blocks'

#### Two Allocater Approaches
1. Implicit
   1. "new" operator implicitly computed the number of bytes needed
   2. Garbage Collector that implicity determined unused bytes and frees them.
2. Explicit
   1. malloc must be explicitly told number of bytes needed
   2. free must be explicitly called to free up the bytes

## Allocator Desing

**Two Goals**:
1. maximize *throughput*: the number of malloc and frees that are handled in some given time frame.
   1. Higher throughput is better, means we can handle more requests
2. maximize *memory utilization*: % of memory used for payload
   1. More is better
   2. memory requested / heap allocated

Trade Off: increasing one decreases the other

#### Requirements
- all allocs use heap
- provide an immediate (fast enough that the code doesn't wait) response
- must handle arbitrary seq. of requests
- must not move or change previously allocated blocks
- must follow memory alignment requirements

#### Design Considerations
- "free block" organization - know where the free blocks are
- placement policy - might want to place differenet requests in diffrent places to render better performance
- split free blocks to improve utilization
- "coalescing" free blocks to create larger a block

