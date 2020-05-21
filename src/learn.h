#ifndef _Learn
#define _Learn
float*** CreateGrad(int* mas_info);
void gradient_mas(
        float*** Weight, float*** Grad, float** Network, int* mas_info, int N);
void learnW(
        float*** Weight,
        int* mas_info,
        float*** Grad,
        int N,
        int* kk,
        float* sred,
        char* s);
#endif
