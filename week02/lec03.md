# Pointers Cont...

- dereference a pointer by prepending it with *
- declare a pointer like so:
```c
int *p2;
```
  
What does the following code do?
```c
int **q = &p1;
```

pointer to a pointer

# 1D arrays

An array is a compound unit of storage storing elements of one type

You access arrays using an identifier and index

allocated as a contiguous block of fized size memory

### how to declare and definie an array

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
  - e.g. printf("%p\n", a)

- A SAA idenitfier used as a destination operand:
  - compiler error! cannot assign a new array to a

# 1D Arrays and Pointers

`int a[5]`
initializes a stack allocated array of size five, looks like this:

a:
| 0  | 1  | 2 |  3 | 4  |
|---|---|---|---|---|
|   |   |  |   |   |

`a[i] === *(a+i)`

we can dereference the address associated with (a+1)

code to create a pointer p having the address of array a above

`int *p = a;`

code to give a[4] 44

*(p+4) = 44;

## Passing Addresses

**call stack tracing**:
- manually tace code with functions in manner that mimics machine
- each function gets a box or a rectangle
  - this is called the stack frame
- stack frame stores parameters, local variables, temporary variables, ...
- the "top box" is the running function
  - those below are waiting for callee return

What is the output of the below code:
```
void f(int pv1, int *pv2, int *pv3, int pv4[]) {
    int lv = pv1 + *pv2 + *pv3 + pv4[0];
    pv1 = 11;
    *pv2 = 22;
    *pv3 = 33;
    pv4[0] = lv;
    pv4[1] = 44;
}
int main(void) {
    int lv1 = 1, lv2 = 2;
    int *lv3;
    int lv4[] = {4,5,6};
    lv3 = lv4 + 2;
    f(lv1, &lv2, lv3, lv4);
    printf("%i,%i,%i\n",lv1,lv2,*lv3);
    printf("%i,%i,%i\n",lv4[0],lv4[1],lv4[2]);
    return 0;
}
```

- pointers: param is a pointer var that gets copy of addr of arg
- arrays: param is a pointer var that gets a copy of addr to array


changing a callee's parameter changes the callee's copy, not the caller's argument.

passing an address requires trust because the callee can change the caller value

# 1D arrays on the heap
(like java)

STACK and HEAP
stack:
- static (fixed in size)
- need to know the size at compile time

heap:
- dynamic allocations during runtime
