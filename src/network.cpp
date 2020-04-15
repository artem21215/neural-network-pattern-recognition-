#include <math.h>
#include <stdio.h>
float sigmoid(float x)
{
    float z;
    z = 1 / (1 + expl(-x));
    printf("%.10f", z);
    return z;
}
