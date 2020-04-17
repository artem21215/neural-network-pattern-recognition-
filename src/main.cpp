#include "input.h"
#include "network.h"
int main()
{
    int *a, kpixel = 0, **Network, ***Weight;
    a = input("files_bmp/1.bmp", a, &kpixel);
    // printpixel(a, kpixel);
    Network = new int*[4];
    Network[0] = new int[kpixel];
    Network[1] = new int[16];
    Network[2] = new int[16];
    Network[3] = new int[10];
    Network[0] = a;
    // printpixel(Network[0], kpixel);
    RandomNetwork(kpixel);
    return 0;
}
