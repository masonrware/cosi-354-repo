# C Funtions

- ### Function:
like a method in java

- ### Caller functions
starts a new function

- ### Callee functions
the function that is being started

1. ## Functions Sharing Data

- ### Argument
data passed to a function

- ### Parameter
variable that stores info in an argument

# Logical Control Flow

1. ## Sequencing
execution - starts in main function
          - flows from top to bottom
            - one statement and then the next
          - each statement is separated by a ;
          - {} indicate blocks of code

2. ## Selection

*Which values mean true? :*

- [ ] true
- [X] 42
- [X] -17
- [ ] 0

*What is output by this code when `money` is 11, -11, 0*

```
if(money == 0)          printf("you're broke\n");
else if (money < 0)     printf("you're in debt");
else                    printf("you've got money\n");
```

- 11: you've got money
- -11: you're in debt
- 0: you've got money

*What is output by this code when the date is 10/31?*

```
if (month == 10) {
    if (day == 31)
        printf("Happy Halloween!\n")
} else
    printf("It's not october.\n")
```

without braces, the else is called a *dangling else*

3. ## Repetition

```
int i = 0;
while (i < 11) {
    printf("%i\n", i);
    i++;
}
```

```
for (int j = 0; j < 11; j++) {
    printf("%i\n", j);
}
```

```
int k = 0;
do {
    printf("%i\n", k);
    k++;
} while (k < 11);
```

# Recall Variables

A scalar variable is a primitive unit of storage

```
void someFunction() {
    int i = 44;
}
```

- ### Aspects of a Variable

idenitifier:    name
value:          data stored
type:           representation of the data
address:        starting location of a variable's memory
size:           number of bits/bytes

**A scalar variable used as a source operand**
e.g. printf("%i\n", i)
**A scalar memeory diagram is**

<img src="./Screen%20Shot%202023-01-26%20at%203.12.19%20PM.png" alt="memory diagram"/>

*byte addressablity*: each address identifies 1 byte

*endianess*: byte ordering for variables that require consecutive bytes in memory
    *little endian*: least significant byte in lowest address
    *big endian*: most significant byte in lowest address

# Pointerzzzz!!!!

A Pointer variable is:
- a scalar variable whose value is a memory address
- similar to Java references but not the exact same

Why?
- for indirect access to memory
- for indirect access to functions
- they are common in C libraries
- for access to MMOI hardware
