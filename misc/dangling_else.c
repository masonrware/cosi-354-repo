#include <stdio.h>

int main(void) {
    int money = 0;

    if(money == 0)          printf("you're broke\n");
    else if (money < 0)     printf("you're in debt");
    else                    printf("you've got money\n");
}
