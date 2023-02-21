# Three Views of Memory

## **Process View = Virtual Memory**

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


## **System View = Illusionist (CS 537)**

Goal: make memory shareable and secure

in process view, all of memory is ours, but the OS needs to create this illusion. It needs to figure out how to share memory between processes.

We do this with:
*pages* which are 4k byte unites of memory blocks managed by the OS

maintains a data structure called the:
*page table* that maps virtual pages (process view) to physical pages (what it actually has)

OS will say "you need this spot out of your virtual page?", ok I'll save it in the page table and cache it in secondary storage or main memory.

## **Hardware View = Physical Memory**
Goal: keep the CPU busy

*memory is slow compared to the CPU

physical address space (PAS):
multi-level hierarchy that ensures that frequently accessed data is close to the CPU.

#### **CPU**
L0: Registers
    fastest medium but it is small

L1: Cache
L2: Cache
L3: Cache (SRAM)

L4: Main Memory (DRAM)

L5: Local Secondary Storage (HDD, SSD)

L6: Network Storage (NAS, Cloud)
 

* * *

32 bit processor = 32-bit addresses = 2^32 = 4,294,967,296 = 4GB address space

`00000000000000000000000000000000=0x00000000` this is the address for the reserved section

the magic number = `0x08048000`
is the base that when added with the canary yields the starting address of your code
this is the starting address of the code segment of your programs virtual memory

### address space:
the range of valid memory addresses for process running

### process:
a running program

### program:
executable source code produced by the compiler/interpreter - sitting on a hard drive somewhere

Windows IA-32 the OS is 2GB, which means there's about 2GB for the user

### kernel:
O.S. address space. The OS is going to be loaded into and out of the physical memory as well

every process knows where the kernel is though so it is for convenience for the programmer.

the kernel is the memory-resident component of the operating system

### user process:
is a running program that is not of the kernel OS, one that the user started

every user process has this simple view of memory

the user has access from the code segment, to the data segment, to the heap, to memory mapped, to the stack

* * *

## CODE Segment

code is divided into sections:
- `.rodata`
- `.text`

instructions are kept in the text segment. The compiler translates source code in C to machine code. Those machine code bianry files are stored in the code segment - in the `.text` segment.

read only data is also in the code segment, in `.rodata`. These are string literals (not character arrays). 

this segment is readable but not writable - not in our architure (C running on Linux).

## DATA Segment

Global variables and static locals are kept in this segment.

data is divided into sections:
- `.bss`
- `.data`

this segment is readable and writable.

## HEAP (more in p3)

is dynamic in size - can grow and shrink.

we can `malloc` more to the heap and `free` up memory in the heap.

In this view of memory, heap grows upward.

## Memory Mapped

Allows a more efficient use of memory. 

Memory mapped is really good for when you know you will need a big chunk of memory but you'll only use it at small rates.

DLL - file I/O, large heap requests


## Stack

is dynamic in size - grows with each function call.

In this view of memory, stack grows downward by pushing things to the top.


addresses printed out in our program are printed from the range of physical addresses in our virtual memory (provided by the CPU).

* * *

## C's Abtract Memory Model

1. CODE Segment
- *contains*: the program - the object code not the source code
  - `.text` section is the binary machine code
  - `.rodata` section is for the string literals
- *Lifetime*: entrie program's execution
- *Initialization*: from the executable object file by the LOADER. Shell starts a process that instructs the OS to load memory with copies of your program and the LOADER is a component of the OS. All happens pre-execution.
- *Access*: READ ONLY

2. DATA segment
- *contains*: global variables and static local variables. static local variables are only available to the function they were declared and defined in and is stored not on the stack. In other words, it persists in memory within the DATA segment. 
- *Lifetime*: entire program's execution. 
- *Initialization*: from EOF by the LOADER before execution begins
  - `.data` section gets initialized from code for variables that are initialized to non-zero values. Only initialized globals and static locals.
  - `.bss` section gets all those globals and static locals that are uninitialized. Forward declared in other words. Also includes all those initialized to zero. BSS stands for Block Started by Symbol.
- *Access*: READ WRITE

3. HEAP
- *contains*: memory that is allocated and freed by the program during execution
- *Lifetime*: managed by the programmer by using malloc/calloc/realloc. 
- *Initialization*: none by default
- *Access*: READ WRITE

4. STACK (AKA Auto Store)
- *contains*: memory in stack frames (or activation record) SF/AR.allocated by function calls and freed by returns

what goes in the stack frame? parameters, local variables, temporary variables
- *Lifetime*: from declaration to the end of scope.
- *Initialization*: none by default
- *Access*: READ WRITE

* * *
## Meet Globals and Static Locals
- global varibales are delcared outside any function
- accessible to all functions in source file
- static local variables are declared inside of functions 
- accessible only in function

```c
#include <stdio.h>
int g = 11;                 // GLOBAL VAR data .data (it's initialized)

void f1 (int p) {           // parameter STACK
    static int x = 22;      // DATA .data (it's initialized)
    x = x + p * g;
    printf("%d\n", x);
}

int main(void) {
    f1(g);
    g = 2;                  // using global g
    int g = 1;              // create a new local variable that shadows the global variable - all g references after are to this local variable STACK
    f1(g);
    reutrn 0;
}
```

*shawdowing*: when a local variable blocks access to the global variable


