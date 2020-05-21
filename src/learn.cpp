#include "input.h"
#include "network.h"
#include <stdio.h>
float*** CreateGrad(int* mas_info)
{
    float*** Grad;
    int i, j;
    Grad = new float**[mas_info[0] - 1];
    for (i = 0; i < (mas_info[0] - 1); i++) {
        Grad[i] = new float*[mas_info[i + 2]];
        for (j = 0; j < mas_info[i + 2]; j++) {
            Grad[i][j] = new float[mas_info[i + 1] + 1];
            for (int jj = 0; jj < (mas_info[i + 1] + 1); jj++)
                Grad[i][j][jj] = 0;
        }
    }
    return Grad;
}

void gradient_mas(
        float*** Weight, float*** Grad, float** Network, int* mas_info, int N)
{
    int i, j, k, y;
    float** dCda;
    dCda = new float*[mas_info[0]];
    for (i = 0; i < mas_info[0]; i++) {
        dCda[i] = new float[mas_info[i + 1]];
        for (j = 0; j < mas_info[i + 1]; j++)
            dCda[i][j] = 0;
    }
    for (i = mas_info[0] - 2; i >= 0; i--) {
        for (j = 0; j < mas_info[i + 2]; j++) {
            if (i == mas_info[0] - 2) {
                if (j == N)
                    y = 1;
                else
                    y = 0;
                dCda[i + 1][j] = 2 * (Network[i + 1][j] - y);
            }
            dCda[i + 1][j] *= Network[i + 1][j] * (1 - Network[i + 1][j]);
            Grad[i][j][mas_info[i + 1]] += dCda[i + 1][j];
            for (k = 0; k < mas_info[i + 1]; k++) {
                Grad[i][j][k] += dCda[i + 1][j] * Network[i][k];
                dCda[i][k] += dCda[i + 1][j] * Weight[i][j][k];
            }
        }
    }
    for (i=0;i<mas_info[0];i++)
        delete[] dCda[i];
    delete[] dCda;
}
void learnW(
        float*** Weight,
        int* mas_info,
        float*** Grad,
        int N,
        int* kk,
        float* sred,
        char* s)
{
    int ed, des, t, i;
    int kpixel;
    float** Network;
    Network=CreateNet(mas_info);
    *kk = 0;
    *sred = 0;
    for (i = 1; i < N; i++) {
        ed = i / 10;
        des = i % 10;
        s[13] = ed + 48;
        s[14] = des + 48;
        Network[0] = input(s, &kpixel);
        t = result(Weight, Network, mas_info);
        if (N==50)
            printf("%d - %d\n",i%10,t);
        *sred += cost(Network, mas_info, i % 10);
        gradient_mas(Weight, Grad, Network, mas_info, i % 10);
        if (t == i % 10)
            *kk += 1;
        delete[] Network[0];
        Network[0]=nullptr;
        // printf("%f ",cost(s,Network,mas_info,i%10));
        // if (*kk>34)
        //   printf("%d - %d\n",i%10,t);
    }
    for (i=0;i<mas_info[0];i++)
        delete[] Network[i];
    delete[] Network;
}
