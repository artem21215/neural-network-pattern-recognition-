#include "input.h"
#include "network.h"
#include <stdio.h>
#include "learn.h"
int main()
{
    int kpixel = 0, *mas_info;
    float *a, ***Weight, **Network,***Grad;
    a = input("files_bmp/1.bmp", a, &kpixel);
    // printpixel(a, kpixel);
    Network = new float*[4];
    Network[0] = new float[kpixel];
    Network[1] = new float[16];
    Network[2] = new float[16];
    Network[3] = new float[10];
    Network[0] = a;
    // printpixel(Network[0], kpixel);
    // RandomNetwork(kpixel);
    Weight = getW(Weight);
    mas_info = get_info(mas_info);
    Grad=CreateGrad(Grad,mas_info);
    printf("%d\n", result(Weight, Network, mas_info));
    return 0;
}
