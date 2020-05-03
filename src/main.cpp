#include "input.h"
#include "learn.h"
#include "network.h"
#include <stdio.h>
int main()
{
    char s[] = "files_bmp/1.bmp";
    int kpixel = 0, *mas_info, i;
    float *a, ***Weight, **Network, ***Grad;
    a = input("files_bmp/01.bmp", a, &kpixel);
    // printpixel(a, kpixel);
    Network = new float*[4];
    Network[0] = new float[kpixel];
    Network[1] = new float[16];
    Network[2] = new float[16];
    Network[3] = new float[10];
    // Network[0] = a;
    // printpixel(Network[0], kpixel);
    // RandomNetwork(kpixel);
    Weight = getW(Weight);
    mas_info = get_info(mas_info);
    Grad = CreateGrad(Grad, mas_info);
    // next: open training example
    char s[] = "files_bmp/  .bmp";
    int ed, des;
    for (i = 0; i < 100; i++) {
        ed = i / 10;
        des = i % 10;
        s[10] = ed + 48;
        s[11] = des + 48;
        a = input(s, a, &kpixel);
        Network[0] = a;
        result(Weight, Network, mas_info);
        gradient_mas(Weight, Grad, Network, mas_info, i % 10);
        // printf("%d\n", result(Weight, Network, mas_info));
    }
    /*    for (i=0;i<mas_info[0]-1;i++)
            for (int j=0;j<mas_info[i+2];j++)
                for (int k=0;k<mas_info[i+1];k++)
                {
                    Grad[i][j][k]/=100;
                    printf("%f ",Grad[i][j][k]);
                }*/
    return 0;
}
