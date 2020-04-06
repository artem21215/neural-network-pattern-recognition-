#include <stdio.h>
#include <stdlib.h>
#include "input.cpp"
void printpixel(int arr[], int n);
int main()
{
    int *a, kpixel = 0;
    a = input("2.bmp", a, &kpixel);
    printpixel(a, kpixel);
    return 0;
}
void printpixel(int arr[], int n)
{
    puts("");
    for (int kk = 0; kk < n; kk++) {
        printf("%d ", arr[kk]);
        if (kk % 10 == 0)
            printf("\n%d - ", kk);
    }
    puts("");
}
