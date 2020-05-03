#include "network.h"
#include <stdio.h>
float*** CreateGrad(float*** Grad, int* mas_info)
{
    int i, j;
    Grad = new float**[mas_info[0] - 1];
    for (i = 0; i < (mas_info[0] - 1); i++) {
        Grad[i] = new float*[mas_info[i + 1]];
        for (j = 0; j < mas_info[i + 1]; j++) {
            Grad[i][j] = new float[mas_info[i + 2]];
            for (int jj = 0; jj < (mas_info[i + 2]); jj++)
                Grad[i][j][jj] = 0;
        }
    }
    return Grad;
}

void gradient_mas(
        float*** Weight, float*** Grad, float** Network, int* mas_info, int N)
{
    int i, j, k, y;
    float summ = 0;
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
                    y = -1;
                dCda[i + 1][j] = 2 * (Network[i + 1][j] - y);
            }
            dCda[i + 1][j] *= Network[i + 1][j] * (1 - Network[i + 1][j]);
            for (k = 0; k < mas_info[i + 1]; k++) {
                Grad[i][j][k] += dCda[i + 1][j] * Network[i][k];
                dCda[i][k] += dCda[i + 1][j] * Weight[i][j][k];
            }
        }
    }
}
