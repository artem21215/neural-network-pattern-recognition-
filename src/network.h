#ifndef _Network
#define _Network
float sigmoid(float x);
void RandomNetwork(int kpixel);
float*** getW();
int* get_info();
int result(float*** Weight, float** Network, int* mas_info);
float VComp(float* W, float* N, int n, float zz);
float difsigmoid(float x);
float cost(char* s, float** Network, int* mas_info, int N);
float** CreateNet(int* mas_info);
void Restruct(char s[], float*** Weight, int* mas_info);
#endif
