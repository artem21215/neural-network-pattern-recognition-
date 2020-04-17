#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float sigmoid(float x)
{
    float z;
    z = 1 / (1 + expl(-x));
    printf("%.10f", z);
    return z;
}

void RandomNetwork(int kpixel)
{
    float p;
    int i, layer = 4, l1 = 16, l2 = 16, l3 = 10;
    FILE* f;
    f = fopen("src/optionnet.dat", "wb");
    fwrite(&layer, sizeof(int), 1, f);
    fwrite(&kpixel, sizeof(int), 1, f);
    fwrite(&l1, sizeof(int), 1, f);
    fwrite(&l2, sizeof(int), 1, f);
    fwrite(&l3, sizeof(int), 1, f);
    srand(time(NULL));
    for (i = 0; i < (kpixel + l1 + l2 + l3); i++) {
        p = float(rand()) / RAND_MAX * 10 - 5;
        fwrite(&p, sizeof(float), 1, f);
    }

    fclose(f);
}
