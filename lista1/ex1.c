#include <stdio.h>

int main(int argc, char const *argv[])
{
    int card = 5, posa = 0, posb = 0, max;
    int a[10] = {15, 13, 10, 9, 7, 5, 3, -1, -12};
    int b[10] = {18, 12, 11, 8, 6, 4, 2, 0, -3};
    while ((posa + posb) < card){
        if (a[posa] > b[posb]){
            max = a[posa];
            posa++;
        }
        else {
            max = b[posb];
            posb++;
        }
    }
    printf("O %d elemento e %d\n", card, max);
    return 0;
}

