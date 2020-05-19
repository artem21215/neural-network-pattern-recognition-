#include "input.h"
#include "learn.h"
#include "network.h"
#include <stdio.h>
#define DELTA 2400
#define NETFILE "../optionnet.dat"
int main()
{
    int kpixel = 0, *mas_info, i;
    float *a, ***Weight, **Network, ***Grad;
    a = input("../files_bmp/01.bmp", &kpixel);
    // RandomNetwork(kpixel);
    Weight = getW(NETFILE);
    mas_info = get_info(NETFILE);
    Network = CreateNet(mas_info);
    Grad = CreateGrad(mas_info);
    delete a;
    char s[] = "../files_bmp/  .bmp";
    int kk, N = 100;
    float sred;
    for (int l = 0; l < 3000; l++) {
        learnW(Network, Weight, mas_info, Grad, N, &kk, &sred, s, a, kpixel);
        if (l % 100 == 0)
            printf("%d ", kk);
        for (i = 0; i < mas_info[0] - 1; i++)
            for (int j = 0; j < mas_info[i + 2]; j++) {
                if (l % 2 == 0) {
                    for (int k = 0; k < mas_info[i + 1]; k++) {
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
    Restruct("../optionnet.dat", Weight, mas_info);
    return 0;
}
