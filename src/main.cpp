#include "input.h"
#include "learn.h"
#include "network.h"
#include <stdio.h>
int main()
{
    int kpixel = 0, *mas_info, i;
    float *a, ***Weight, **Network, ***Grad;
    a = input("files_bmp/01.bmp", a, &kpixel);
    //RandomNetwork(kpixel);
    Weight = getW(Weight);
    mas_info = get_info(mas_info);
    Network=CreateNet(Network,mas_info);
    Grad = CreateGrad(Grad, mas_info);
    // next: open training example
    char s[] = "files_bmp/  .bmp";
    int kk,N=100;
    float sred;
for (int l=0;l<1000;l++){
    learnW(Network,Weight,mas_info,Grad,N,&kk,&sred,s,a,kpixel);
    if (l%100==0)
        printf("%d ",kk);
    for (i=0;i<mas_info[0]-1;i++)
        for (int j=0;j<mas_info[i+2];j++){
            if (l%2==0){
                for (int k=0;k<mas_info[i+1];k++){
                    Weight[i][j][k]-=Grad[i][j][k]/100;
                    Grad[i][j][k]=0;
                }
            }
            else{
            Weight[i][j][mas_info[i+1]]-=Grad[i][j][mas_info[i+1]]/100;
            Grad[i][j][mas_info[i+1]]=0;
            }
        }
    sred/=100;
    if (l%100==0)
        printf("%f\n",sred);
}
Restruct("src/optionnet.dat", Weight, mas_info);
    return 0;
}
