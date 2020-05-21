#include "input.h"
#include "learn.h"
#include "network.h"
#include <stdio.h>
#define DELTA 1000
#define NETFILE "../optionnet.dat"
int main()
{
    int kpixel = 0, *mas_info, i;
    float *a, ***Weight, ***Grad;
    char s[] = "../files_bmp/  .bmp";
    int kk, N = 100, j, k, l;
    float sred;
    char sel;
    printf("Mode select:\n");
    printf("1 - for analysis\n");
    printf("2 - for learning\n");
    sel = getchar();
    a = input("../files_bmp/01.bmp", &kpixel);
    // RandomNetwork(NETFILE,kpixel);
    Weight = getW(NETFILE);
    mas_info = get_info(NETFILE);
    Grad = CreateGrad(mas_info);
    delete[] a;
    switch (sel) {
    case '2':
        for (l = 0; l < 10000; l++) {
            learnW(Weight, mas_info, Grad, N, &kk, &sred, s);
            if (l % 100 == 0)
                printf("%d ", kk);
            for (i = 0; i < mas_info[0] - 1; i++)
                for (j = 0; j < mas_info[i + 2]; j++) {
                    if (l % 2 == 0) {
                        for (k = 0; k < mas_info[i + 1]; k++) {
                            Weight[i][j][k] -= Grad[i][j][k] / DELTA;
                            Grad[i][j][k] = 0;
                        }
                    } else {
                        Weight[i][j][mas_info[i + 1]]
                                -= Grad[i][j][mas_info[i + 1]] / DELTA;
                        Grad[i][j][mas_info[i + 1]] = 0;
                    }
                }
            sred /= 100;
            if (l % 100 == 0)
                printf("%f\n", sred);
        }
        Restruct(NETFILE, Weight, mas_info);
        break;
    case '1':
        for (l = 0; l < 1; l++) {
            learnW(Weight, mas_info, Grad, 50, &kk, &sred, s);
        }
        break;
    }
    return 0;
}
