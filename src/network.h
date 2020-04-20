#ifndef _Network
#define _Network
float sigmoid(float x);
void RandomNetwork(int kpixel);
float*** getW(float*** Weight);
int* get_info(int* mas_info);
int result(float*** Weight, float** Network, int* mas_info);
float VComp(float* W, float* N, int n);
#endif
