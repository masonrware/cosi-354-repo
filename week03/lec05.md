# Command Line Arguments

```shell
$gcc myprog.c -Wall -m32 -std=gnu99 -o myprog
```
command followed by program args

How to use arguments?

```c
int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    return 0;
}
```

 - arv is an array of pointers to chars

## 2D arrays

make a 2d array pointer named m

```c
int **m;
```

assign m an "array of arrays"

```c
m = malloc(size*sizeof(int *));
if(m==NULL){printf("....");}
```

assign each element in the "array of arrays" its own row of ints.

```c
*(m+n) = malloc(size*sizeof(int));
```

Write the code to free the heap allocated 2d array

```c
for(int i=0; i<size; i++){
    free(*(m+i));
}
free(m); m=NULL;
```
****