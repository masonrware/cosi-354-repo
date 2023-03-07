# Heap Allocator Cont.

**the p-bit.**

Free and allocated block headers will also encode a p-bit

this bit indicates wether or not the block previous is free or alloc'd


What integer value will the header value for an allocated block that is:

1. 8 bytes in size and prev. block is free?
0000001001 = 9
2. 8 bytes in size and prev. block is allocated?
0000001011 = 11
3. 32 bytes in size and prev. block is allocated?
0100000011 = 35

Given a pointer to a payload, how do you get to the header of aprevious block if it's free?
1. get curr header : ptr-4
2. check pbit : if pbit is 0, prev block is free and has a footer
3. gett to prev block footer by ptr-8 or header-4

Now we can coalesce the blocks by editing the previous block's header!

An allocator using an expliit free list only kjeeps list of free blocks
The efl can be stored in heap itself by specifying a new layout for free blocks

EFL takes form of a heap free block with a footer

EFL has a header and and a footer and the contents are 4 byte chunks that store pointers to the previous and next free blocks in the heap.

Minimum free block size in the EFL are 16 bits = 4 bytes for header + 4 for prev ptr + 4 for sec. ptr + 4 for footer

resembles a doubly linked list

### Explixit Free List Improvements

**Free List ORdering**

address order:
 - maintain addr orer of free blocks
 - malloc with FF is a little faster
 - free is a little slower

last-in order:
  - most recently freed block is linked to the front of the list
  - malloc with FF is slower
  - free is a little faster

**Free List Segregation**
keep array of free list one for each size
malloc chooses appropriate list

simple segregation:
  - One free list for each block size
  - strcture is simple - no header is needed
  - fast, choose free block fro correct list
  - if the free list is empty, get more heap, divide into desired or split into a larger block
  - free is fast O(1)
  - problem is that we have more internal and external fragmentation

fitted segregation:
  - One free list for each size range
  - fitting uses FF of appropriate size range, and then search larger size if that fails to find a free block
  - put the new free block into list of approp. size
  - 