# Simple View of Heap

### Rotated Linear Memory Layout

1 word = 4 bytes.

double word alignment: block size must be a multiple of 8

add bytes of padding onto non-8-multiple blocks of mem.

External Fragmentation: when there is engouh heap memory but it is divided in blocks that are too small.

Internal Fragmentation: when heap memory in a block is used for OVERHEAD

### Free Block Organization

The simple view of the allocator has no way to determine the size and status of each block.

- size is the number of bytes in the heap block
    - includes the overhead
- status is if it is free'd or alloc'd

#### Explicit Free List

Allocator uses a data structure containing just free blocks 

keeps track of size and start address of free blocks

#### Implicit Free List

Allocator uses heap blocks themselves for the data strcuture

must track the size and status of each block

upside is that there is less space - no need for external data structure.

First word of each block is a header

