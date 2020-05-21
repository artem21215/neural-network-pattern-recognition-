#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float VComp(float* W, float* N, int n, float zz);
float sigmoid(float x)
{
    return 1 / (1 + expl(-x));
}
void RandomNetwork(const char s[], int kpixel)
{
    float p;
    int i, layer = 4, l1 = 16, l2 = 16, l3 = 10;
    FILE* f;
    f = fopen(s, "wb");
    fwrite(&layer, sizeof(int), 1, f);
    fwrite(&kpixel, sizeof(int), 1, f);
    fwrite(&l1, sizeof(int), 1, f);
    fwrite(&l2, sizeof(int), 1, f);
    fwrite(&l3, sizeof(int), 1, f);
    srand(time(NULL));
    for (i = 0; i < (kpixel * l1 + l1 * l2 + l2 * l3 + l1 + l2 + l3); i++) {
        p = float(rand()) / RAND_MAX * 10 - 5;
        fwrite(&p, sizeof(float), 1, f);
    }

    fclose(f);
}

float** CreateNet(int* mas_info)
{
    int i, j;
    float** Network;
    Network = new float*[mas_info[0]];
    for (i = 0; i < mas_info[0]; i++) {
        Network[i] = new float[mas_info[i + 1]];
        for (j = 0; j < mas_info[i + 1]; j++)
            Network[i][j] = 0;
    }
    return Network;
}

float*** getW(const char s[])
{
    float*** Weight;
    FILE* f;
    int nn, *mas_lay, i, j, k;
    f = fopen(s, "rb");
    fread(&nn, sizeof(int), 1, f);
    Weight = new float**[nn - 1];
    mas_lay = new int[nn];
    for (i = 0; i < nn; i++)
        fread(&mas_lay[i], sizeof(int), 1, f);
    for (i = 0; i < nn - 1; i++) {
        Weight[i] = new float*[mas_lay[i + 1]];
        for (j = 0; j < mas_lay[i + 1]; j++)
            Weight[i][j] = new float[mas_lay[i] + 1];
    }

    for (i = 0; i < nn - 1; i++) {
        for (j = 0; j < mas_lay[i + 1]; j++) {
            for (k = 0; k < mas_lay[i] + 1; k++) {
                fread(&Weight[i][j][k], sizeof(float), 1, f);
            }
        }
    }
    delete[] mas_lay;
    fclose(f);
    return Weight;
}

int* get_info(const char s[])
{
    int* mas_info;
    FILE* f;
    int nn;
    f = fopen(s, "rb");
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
    float zz;
    for (i = 1; i < mas_info[0]; i++)
        for (j = 0; j < mas_info[i + 1]; j++) {
            zz = Weight[i - 1][j][mas_info[i]];
            Network[i][j]
                    = VComp(Weight[i - 1][j], Network[i - 1], mas_info[i], zz);
        }
    int maxx = 0;
    for (i = 1; i < mas_info[mas_info[0]]; i++) {
        if (Network[mas_info[0] - 1][i] > Network[mas_info[0] - 1][maxx])
            maxx = i;
    }
    return maxx;
}

float VComp(float* W, float* N, int n, float zz)
{
    int i;
    float summ = 0;
    for (i = 0; i < n; i++)
        summ += W[i] * N[i];
    summ = sigmoid(summ + zz);
    return summ;
}

float cost(float** Network, int* mas_info, int N)
{
    int i;
    float c = 0;
    for (i = 0; i < mas_info[mas_info[0]]; i++)
        if (N == i)
            c += (Network[mas_info[0] - 1][i] - 1)
                    * (Network[mas_info[0] - 1][i] - 1);
        else
            c += (Network[mas_info[0] - 1][i] + 0)
                    * (Network[mas_info[0] - 1][i] + 0);
    return c;
}

void Restruct(const char s[], float*** Weight, int* mas_info)
{
    FILE* f;
    int i, j, k;
    f = fopen(s, "wb");
    for (i = 0; i < mas_info[0] + 1; i++)
        fwrite(&mas_info[i], sizeof(int), 1, f);
    for (i = 0; i < mas_info[0] - 1; i++) {
        for (j = 0; j < mas_info[i + 2]; j++) {
            for (k = 0; k < mas_info[i + 1] + 1; k++) {
                fwrite(&Weight[i][j][k], sizeof(float), 1, f);
            }
        }
    }
    fclose(f);
}
