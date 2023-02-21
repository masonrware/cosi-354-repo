#include <stdio.h>

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