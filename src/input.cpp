#include <stdio.h>
#include <stdlib.h>
void bitetobin(int z, int b[]);
float* input(char s[20], float arr[], int* kpixel)
{
    FILE* f;
    int width, hight;
    int i, j, z, bitpix = 0, bitew, b[8];
    for (i = 0; i < 8; i++)
        b[i] = 0;
    f = fopen(s, "rb");
    fseek(f, 18, SEEK_SET);
    fread(&width, 4, 1, f);
    fseek(f, 22, SEEK_SET);
    fread(&hight, 4, 1, f);
    fseek(f, 28, SEEK_SET);
    fread(&bitpix, 2, 1, f);
    *kpixel = width * hight;
    arr = new float[width * hight];
    // 2 color and 4 bite min * bitpix
    fseek(f, 54 + 4 * bitpix * 2, SEEK_SET);
    // 8 pixel in bite. min=4 bite, 4*8=32 pixel
    if (width % 32 != 0)
        bitew = width / 32 + 1;
    else
        bitew = width / 32;
    bitew *= 4;
    j = 0;
    int p = 0;
    for (int gg = 0; gg < hight; gg++) {
        for (i = 0; i < bitew; i++) {
            z = 0;
            fread(&z, 1, 1, f);
            for (int j = 0; j < 8; j++)
                b[j] = 0;

            bitetobin(z, b);
            for (int jj = 0; jj < 8; jj++) {
                if (p % (bitew * 8) < width) {
                    arr[j] = b[p % 8];
                    j++;
                }
                p++;
            }
        }
    }
    fclose(f);
    return arr;
}

void bitetobin(int z, int b[])
{
    int i = 1, summ = 1, ii = 0;
    while (i <= z) {
        i *= 2;
        summ++;
    }
    summ--;
    ii = 8 - summ;
    i /= 2;
    summ = 0;

    while (i > 0) {
        if (summ + i <= z) {
            b[ii] = 1;
            summ += i;
        } else {
            b[ii] = 0;
        }
        ii++;
        i /= 2;
    }
}

void printpixel(int arr[], int n)
{
    puts("");
    for (int kk = 0; kk < n; kk++) {
        printf("%d ", arr[kk]);
        if (kk % 28 == 0)
            printf("\n%d - ", kk);
    }
    puts("");
}

