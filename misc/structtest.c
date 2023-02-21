#include <stdio.h>
#include "structtest_header.h"

//typedef struct {
//   char * name;
//} MyStruct;

int main(void) {
   MyStruct me = {"mason"};
   printf("%s\n", me.name);
}
