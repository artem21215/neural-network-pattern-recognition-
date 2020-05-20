#ifndef _Network
#define _Network
float sigmoid(float x);
void RandomNetwork(int kpixel);
float*** getW(const char s[]);
int* get_info(const char s[]);
int result(float*** Weight, float** Network, int* mas_info);
float VComp(float* W, float* N, int n, float zz);
float cost(float** Network, int* mas_info, int N);
float** CreateNet(int* mas_info);
void Restruct(const char s[], float*** Weight, int* mas_info);
#endif
