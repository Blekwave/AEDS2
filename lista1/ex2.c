#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a[15] = {15,14,13,12,11,9,8,7,6,5,4,3,2,1,0};
    int elemento = 10;
    int i = 0;
    while (i < 15 && elemento <= a[i])
        i++;
    printf("%d\n", i);
    return 0;
}