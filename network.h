#include <stdio.h>
#include <math.h>

float sigmoid(float x){
float z;
  z = 1/(1 + expl(-x));
  printf("%.10f", z);
return z;
}
