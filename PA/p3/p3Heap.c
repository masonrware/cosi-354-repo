///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission SPRING 2023, CS354-deppeler
//
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "p3Heap.h"

/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block but only containing size.
 */
typedef struct blockHeader
{

    int size_status;

    /*
     * Size of the block is always a multiple of 8.
     * Size is stored in all block headers and in free block footers.
     *
     * Status is stored only in headers using the two least significant bits.
     *   Bit0 => least significant bit, last bit
     *   Bit0 == 0 => free block
     *   Bit0 == 1 => allocated block
     *
     *   Bit1 => second last bit
     *   Bit1 == 0 => previous block is free
     *   Bit1 == 1 => previous block is allocated
     *
     * Start Heap:
     *  The blockHeader for the first block of the heap is after skip 4 bytes.
     *  This ensures alignment requirements can be met.
     *
     * End Mark:
     *  The end of the available memory is indicated using a size_status of 1.
     *
     * Examples:
     *
     * 1. Allocated block of size 24 bytes:
     *    Allocated Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 25
     *      If the previous block is allocated p-bit=1 size_status would be 27
     *
     * 2. Free block of size 24 bytes:
     *    Free Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 24
     *      If the previous block is allocated p-bit=1 size_status would be 26
     *    Free Block Footer:
     *      size_status should be 24
     */
} blockHeader;

/*
 * Global variables
 */
blockHeader *heap_start = NULL;
blockHeader *end_mark = NULL;
int alloc_size;

/*
 * This is a best fit algorithm for finding the best fit block
 * within the current heap.
 */
blockHeader *bestFit()
{
    int curr_size;

    blockHeader *current = heap_start;
    blockHeader *bestFitBlock = NULL;

    while (current->size_status != 1)
    {
        curr_size = current->size_status;

        // record actual size of block in curr_size
        if (curr_size & 1)
        {
            // LSB = 1 => used block
            curr_size = curr_size - 1;
        }
        else
        {
            // LSB = 0 => free block
            if (curr_size >= alloc_size)
            {
                if (!(bestFitBlock) || curr_size < (bestFitBlock->size_status))
                {
                    // set bestFitBlock to current
                    bestFitBlock = current;
                }
            }
        }

        if (curr_size & 2)
        {
            curr_size = curr_size - 2;
        }

        current = (blockHeader *)((char *)current + curr_size);
    }

    return bestFitBlock;
}

/*
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block (payload) on success.
 * Returns NULL on failure.
 *
 * This function must:
 * - Check size - Return NULL if size < 1
 * - Determine block size rounding up to a multiple of 8
 *   and possibly adding padding as a result.
 *
 * - Use BEST-FIT PLACEMENT POLICY to chose a free block
 *
 * - If the BEST-FIT block that is found is exact size match
 *   - 1. Update all heap blocks as needed for any affected blocks
 *   - 2. Return the address of the allocated block payload
 *
 * - If the BEST-FIT block that is found is large enough to split
 *   - 1. SPLIT the free block into two valid heap blocks:
 *         1. an allocated block
 *         2. a free block
 *         NOTE: both blocks must meet heap block requirements
 *       - Update all heap block header(s) and footer(s)
 *              as needed for any affected blocks.
 *   - 2. Return the address of the allocated block payload
 *
 *   Return NULL if unable to find and allocate block for required size
 *
 * Note: payload address that is returned is NOT the address of the
 *       block header.  It is the address of the start of the
 *       available memory for the requester.
 *
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void *balloc(int size)
{
    blockHeader *target;
    int padsize;

    if (size <= 0)
    {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return NULL;
    }

    // add bytes for header
    alloc_size = size + sizeof(blockHeader);

    // calculate padsize as the padding required to round up size
    // to a multiple of 8
    padsize = alloc_size % 8;
    padsize = (8 - padsize) % 8;

    alloc_size = alloc_size + padsize;

    // returns pointer to HEADER
    blockHeader *bestFitBlock = bestFit();

    if (bestFitBlock == NULL)
    {
        return NULL;
    }

    int old_block_size = bestFitBlock->size_status;

    if (old_block_size & 1)
    {
        old_block_size -= 1;
    }
    if (old_block_size & 2)
    {
        old_block_size -= 2;
    }

    // compare the raw sizes (can only be greater than or equal to thanks to bestFit())
    if (old_block_size > alloc_size && (old_block_size - alloc_size >= 8))
    {
        // jump to next header
        target = (blockHeader *)((void *)bestFitBlock + alloc_size);
        if (target->size_status != 1)
        {
            target->size_status = (old_block_size - alloc_size);

            blockHeader *footer = ((void *)target + (target->size_status - 4));
            footer->size_status = (old_block_size - alloc_size);

            // indicate previous is alloc'd
            target->size_status += 2;
        }
    }
    else
    {
        // need to reset the next header regardless, but not its size nor the footer
        target = (blockHeader *)((void *)bestFitBlock + alloc_size);
        if (target->size_status != 1)
        {
            // indicate previous is alloc'd
            target->size_status += 2;
        }
    }

    // check what the p-bit was and copy it over
    if (bestFitBlock->size_status & 2)
    {
        alloc_size += 2;
    }

    // reset current size
    bestFitBlock->size_status = alloc_size;
    // (bestFitBlock->size_status | alloc_size)

    // indicate it is alloc'd
    bestFitBlock->size_status += 1;

    return (blockHeader *)((void *)bestFitBlock + 4);
}

/*
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - Update header(s) and footer as needed.
 */
int bfree(void *ptr)
{
    // if pointer is NULL
    if (ptr == NULL)
    {
        return -1;
    }
    unsigned int alignment = (unsigned int)(ptr);
    // if pointer is not 8 byte aligned
    if (alignment % 8 != 0)
    {
        return -1;
    }
    // if pointer is outside the range of memory allocated by init_heap()
    else if ((unsigned int)ptr < (unsigned int)heap_start || (unsigned int)ptr >= (unsigned int)end_mark)
    {
        return -1;
    }
    // if the pointer points to a free block
    else if (!((((blockHeader *)(ptr - 4))->size_status) & 1))
    {
        return -1;
    }

    // go to the header of the block to be deleted
    blockHeader *target = ptr - 4;

    // take out the size of the header
    int target_size = target->size_status - 4;

    if (target_size & 1)
    {
        target_size -= 1;
    }
    if (target_size & 2)
    {
        target_size -= 2;
    }

    // indicate it is freed
    target->size_status -= 1;

    blockHeader *footer = (ptr + (target_size - 4));
    footer->size_status = target_size + 4;

    blockHeader *next_header = (ptr + target_size);

    // if not the end
    if (next_header->size_status != 1)
    {
        // set the p-bit to 0
        next_header->size_status -= 2;
    }

    return 0;
}

/*
 * Function for traversing heap block list and coalescing all adjacent
 * free blocks.
 *
 * This function is used for user-called coalescing.
 * Updated header size_status and footer size_status as needed.
 */
int coalesce()
{
    int coalesced_blocks, curr_size = 0;

    blockHeader *current = heap_start;

    while (current->size_status != 1)
    {
        curr_size = current->size_status;

        // if the current block is free and the previous is free
        if (!(curr_size & 1) && !(curr_size & 2))
        {
            blockHeader *prev_footer = ((void *)current - 4);
            blockHeader *prev_header = ((void *)current - (prev_footer->size_status));

            prev_header->size_status += curr_size;
            int cleaned_size = prev_header->size_status + curr_size;
            if (cleaned_size & 1)
            {
                cleaned_size -= 1;
            }
            if (cleaned_size & 2)
            {
                cleaned_size -= 2;
            }

            blockHeader *footer = ((void *)current + (curr_size - 4));
            footer->size_status = cleaned_size - curr_size;

            coalesced_blocks += 1;
        }
        else
        {
            if (curr_size & 1)
            {
                curr_size -= 1;
            }
            if (curr_size & 2)
            {
                curr_size -= 2;
            }
        }

        current = (blockHeader *)((char *)current + curr_size);
    }

    return coalesced_blocks;
}

/*
 * Function used to initialize the memory allocator.
 * Intended to be called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */
int init_heap(int sizeOfRegion)
{

    static int allocated_once = 0; // prevent multiple myInit calls

    int pagesize;   // page size
    int padsize;    // size of padding when heap size not a multiple of page size
    void *mmap_ptr; // pointer to memory mapped area
    int fd;

    if (0 != allocated_once)
    {
        fprintf(stderr,
                "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }

    if (sizeOfRegion <= 0)
    {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize from O.S.
    pagesize = getpagesize();

    // Calculate padsize as the padding required to round up sizeOfRegion
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    alloc_size = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd)
    {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr)
    {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }

    allocated_once = 1;

    // for double word alignment and end mark
    alloc_size -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heap_start = (blockHeader *)mmap_ptr + 1;

    // Set the end mark
    end_mark = (blockHeader *)((void *)heap_start + alloc_size);
    end_mark->size_status = 1;

    // Set size in header
    heap_start->size_status = alloc_size;

    // Set p-bit as allocated in header
    // note a-bit left at 0 for free
    heap_start->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader *)((void *)heap_start + alloc_size - 4);
    footer->size_status = alloc_size;

    return 0;
}

/*
 * Function can be used for DEBUGGING to help you visualize your heap structure.
 * Traverses heap blocks and prints info about each block found.
 *
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts)
 * t_End    : address of the last byte in the block
 * t_Size   : size of the block as stored in the block header
 */
void disp_heap()
{

    int counter;
    char status[6];
    char p_status[6];
    char *t_begin = NULL;
    char *t_end = NULL;
    int t_size;

    blockHeader *current = heap_start;
    counter = 1;

    int used_size = 0;
    int free_size = 0;
    int is_used = -1;

    fprintf(stdout,
            "*********************************** HEAP: Block List ****************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout,
            "---------------------------------------------------------------------------------\n");

    while (current->size_status != 1)
    {
        t_begin = (char *)current;
        t_size = current->size_status;

        if (t_size & 1)
        {
            // LSB = 1 => used block
            strcpy(status, "alloc");
            is_used = 1;
            t_size = t_size - 1;
        }
        else
        {
            strcpy(status, "FREE ");
            is_used = 0;
        }

        if (t_size & 2)
        {
            strcpy(p_status, "alloc");
            t_size = t_size - 2;
        }
        else
        {
            strcpy(p_status, "FREE ");
        }

        if (is_used)
            used_size += t_size;
        else
            free_size += t_size;

        t_end = t_begin + t_size - 1;

        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%4i\n", counter, status,
                p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);

        current = (blockHeader *)((char *)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout,
            "---------------------------------------------------------------------------------\n");
    fprintf(stdout,
            "*********************************************************************************\n");
    fprintf(stdout, "Total used size = %4d\n", used_size);
    fprintf(stdout, "Total free size = %4d\n", free_size);
    fprintf(stdout, "Total size      = %4d\n", used_size + free_size);
    fprintf(stdout,
            "*********************************************************************************\n");
    fflush(stdout);

    return;
}

// end p3Heap.c (Spring 2023)
