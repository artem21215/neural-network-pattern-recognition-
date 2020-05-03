#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float VComp(float* W, float* N, int n);
float sigmoid(float x)
{
    return 1 / (1 + expl(-x));
}

float difsigmoid(float x)
{
    return 1/(2+expl(-x)+expl(x));
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
    for (i = 0; i < (kpixel * l1 + l1 * l2 + l2 * l3); i++) {
        p = float(rand()) / RAND_MAX * 10 - 5;
        fwrite(&p, sizeof(float), 1, f);
    }

    fclose(f);
}

float*** getW(float*** Weight)
{
    FILE* f;
    int nn, *mas_lay, i, j, k;
    f = fopen("src/optionnet.dat", "rb");
    fread(&nn, sizeof(int), 1, f);
    Weight = new float**[nn - 1];
    mas_lay = new int[nn];
    for (i = 0; i < nn; i++)
        fread(&mas_lay[i], sizeof(int), 1, f);
    for (i = 0; i < nn - 1; i++) {
        Weight[i] = new float*[mas_lay[i + 1]];
        for (j = 0; j < mas_lay[i + 1]; j++)
            Weight[i][j] = new float[mas_lay[i]];
    }

    for (i = 0; i < nn - 1; i++) {
        for (j = 0; j < mas_lay[i + 1]; j++) {
            for (k = 0; k < mas_lay[i]; k++) {
                fread(&Weight[i][j][k], sizeof(float), 1, f);
            }
        }
    }

    fclose(f);
    return Weight;
}

int* get_info(int* mas_info)
{
    FILE* f;
    int nn;
    f = fopen("src/optionnet.dat", "rb");
    fread(&nn, sizeof(int), 1, f);
    mas_info = new int[nn + 1];
    mas_info[0] = nn;
    for (int i = 1; i < nn + 1; i++)
        fread(&mas_info[i], sizeof(int), 1, f);
    fclose(f);
    return mas_info;
}

int result(float*** Weight, float** Network, int* mas_info)
{
    int i, j;
    for (i = 1; i < mas_info[0]; i++)
        for (j = 0; j < mas_info[i + 1]; j++)
            Network[i][j]
                    = VComp(Weight[i - 1][j], Network[i - 1], mas_info[i]);
    int maxx = 0;
    for (i = 1; i < mas_info[mas_info[0]]; i++)
        if (Network[mas_info[0] - 1][i] > Network[mas_info[0] - 1][maxx])
            maxx = i;
    return maxx;
}

float VComp(float* W, float* N, int n)
{
    int i;
    float summ = 0;
    for (i = 0; i < n; i++)
        summ += W[i] * N[i];
    summ = sigmoid(summ);
    return summ;
}

float cost(char* s, float** Network, int* mas_info,int N)
{
    int i;
    float c = 0;
    for (i = 0; i < mas_info[mas_info[0]]; i++)
            if (N == i)
              c += (Network[mas_info[0]-1][i]-1)*(Network[mas_info[0]-1][i]-1);
            else c += (Network[mas_info[0]-1][i]+1)*(Network[mas_info[0]-1][i]+1);
    return c;
}
