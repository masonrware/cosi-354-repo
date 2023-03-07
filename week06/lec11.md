# Dynamic Memory Allocator Continued

### Placement Policies:

A placement policy is an algorithm used to search the heap for free blocks

- **First Fit(FF)**
  - start from: the beginning of the heap.
  - stop at: the first free block that is big enough.
  - fail if: we reach the end mark.

mem util: (GOOD) likely to choose a free block that is close to the desired size.
thruput: (BAD) requires lots of skips to get to large blocks.

- **Next Fit(NF)**
  - start from: the most recently allocated block.
  - stop at: the first free block that is big enough.
  - fail if: if we hit the start again.

mem util: (NOT AS GOOD) we might choose a block that is too big.
thruput: (A LITTLE BETTER) faster than FF because we don't have to search through all the small blocks all the time.

- **Best Fit(BF)**
  - start from: beginning of heap
  - stop at: END block and choose the one that is closest
    - or stop early if we find the exact size
  - fail if: no block is big enough

mem util: 
thruput:


What happens if the free block chosen is bigger than the request?

- ENTIRE BLOCK
  - mem util: less because of wasted space --> internal fragmentation
  - thruput: fast and simple code

- SPLIT INTO TWO BLOCKS - ALLOCD & FREED
  - mem util: less internal fragmentation
  - thruput: slower to search, more heap block

What happens if there isn't a large enough free block to satisfy request?

1. Coalesce free blocks (only if adjacent)
2. Request more memory from the OS
3. return `NULL`, alloc fails

### Coalescing

merging together of consecutive free blocks to generate a larger free block

Types of coalescing:
*immediate*: coalesce the next and previous blocks every time you free a block
*delayed*: coalesce only when needed by alloc operation.

Given a pointer to a payload, find its header:
```c
(void *)ptr - sizeof(blockHeader); 
```

Given a pointer to a payload, find the header of the next block:
```c
((void *)ptr - sizeof(blockHeader)) + //curr size of block; 
```


