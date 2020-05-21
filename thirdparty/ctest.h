#include "input.h"
#include "learn.h"
#include "network.h"
#include <stdio.h>
#include <cxxtest/TestSuite.h>
class MoveTest : public CxxTest::TestSuite {
public:
    void test_sigm(void)
    {
        TS_ASSERT_EQUALS(sigmoid(0),0.5);
        TS_ASSERT(sigmoid(1000000)<=1);
        TS_ASSERT(sigmoid(1000000)>0.9);
        TS_ASSERT(sigmoid(-1000000)>=0);
        TS_ASSERT(sigmoid(-1000000)<0.1);
    }
public:
    void test_bitetobin(void)
    {
        int b[8],l,z;
        for (int i=0;i<256;i++){
            l=0;
            z=1;
            bitetobin(i, b);
            for (int j=7;j>=0;j--){
                if (b[j]==1)
                    l+=z;
                z*=2;
            }
            TS_ASSERT_EQUALS(l,i);
        }
    }
public:
    void test_input(void)
    {
        float* a;
        int kpixel;
        a=input("../thirdparty/testfiles/wb.bmp",&kpixel);
        for (int i=0;i<kpixel/2;i++)
            TS_ASSERT_EQUALS(a[i],0);
        for (int i=kpixel/2;i<kpixel;i++)
            TS_ASSERT_EQUALS(a[i],1);
        a=input("../thirdparty/testfiles/bw.bmp",&kpixel);
        for (int i=0;i<kpixel/2;i++)
            TS_ASSERT_EQUALS(a[i],1);
        for (int i=kpixel/2;i<kpixel;i++)
            TS_ASSERT_EQUALS(a[i],0);
        a=input("../thirdparty/testfiles/bw2.bmp",&kpixel);
        for (int i=0;i<kpixel;i++){
            if (i%28<14){
                TS_ASSERT_EQUALS(a[i],0);
            }
            else
                TS_ASSERT_EQUALS(a[i],1);
        }
    }
public:
    void test_getW(void)
    {
        int i,j;
        float*** w;
        float z;
        FILE* f;
        char s[]="../thirdparty/testfiles/1.dat";
        f=fopen(s,"rb");
        w=getW(s);
        for (i=0;i<5;i++)
            fread(&z,sizeof(int),1,f);
        for (i=0;i<16;i++)
            for (j=0;j<785;j++){
                fread(&z,sizeof(float),1,f);
                TS_ASSERT_EQUALS(z,w[0][i][j]);
                z++;
            }
        for (i=0;i<16;i++)
            for (j=0;j<17;j++){
                fread(&z,sizeof(float),1,f);
                TS_ASSERT_EQUALS(z,w[1][i][j]);
                z++;
            }
        for (i=0;i<10;i++)
            for (j=0;j<17;j++){
                fread(&z,sizeof(float),1,f);
                TS_ASSERT_EQUALS(z,w[2][i][j]);
                z++;
            }
        fclose(f);
    }
public:
    void test_get_info(void)
    {
        int* a;
        a=get_info("../thirdparty/testfiles/1.dat");
        TS_ASSERT_EQUALS(a[0],4);
        TS_ASSERT_EQUALS(a[1],784);
        TS_ASSERT_EQUALS(a[2],16);
        TS_ASSERT_EQUALS(a[3],16);
        TS_ASSERT_EQUALS(a[4],10);
    }
public:
    void test_result(void)
    {
        float*** w;
        float** n;
        int *inf,i,j,k;
        inf=new int[4];
        inf[0]=3;
        inf[1]=5;
        inf[2]=3;
        inf[3]=2;
        n=CreateNet(inf);
        w=new float**[inf[0]-1];
        for (i=0;i<inf[0]-1;i++){
            w[i]=new float*[inf[i+2]];
            for (j=0;j<inf[i+2];j++){
                w[i][j]=new float[inf[i+1]+1];
            }
        }
        for (i=0;i<inf[1];i++)
            n[0][i]=i+1;
        float z=++i;
        for (i=0;i<inf[0]-1;i++)
            for (j=0;j<inf[i+2];j++)
                for (k=0;k<inf[i+1]+1;k++)
                    w[i][j][k]=z++;
        w[0][0][5]=-129;
        w[0][1][5]=-225;
        w[0][2][5]=-305;
        w[1][0][3]=-44;
        w[1][1][3]=-50;
        result(w,n,inf);
        TS_ASSERT_EQUALS(n[1][0],sigmoid(1));
        TS_ASSERT_EQUALS(n[1][1],sigmoid(-5));
        TS_ASSERT_EQUALS(n[1][2],sigmoid(5));
        TS_ASSERT_EQUALS(n[2][0],VComp(w[1][0],n[1],3,-44));
        TS_ASSERT_EQUALS(n[2][1],VComp(w[1][1],n[1],3,-50));
        TS_ASSERT((int)(sigmoid(0.2658)-n[2][0])<1);
        TS_ASSERT((int)(sigmoid(0.4584)-n[2][1])<1);
        
    }
public:
    void test_cost(void)
    {
        int inf[3];
        float **n;
        inf[0]=2;
        inf[1]=3;
        inf[2]=2;
        n=CreateNet(inf);
        n[1][0]=0;
        n[1][1]=1;
        TS_ASSERT_EQUALS(cost(n,inf,1),0);
        TS_ASSERT_EQUALS(cost(n,inf,0),2);
    }
public:
    void test_restruct(void)
    {
        int inf[3];
        float ***w,***W;
        const char s[]="../thirdparty/testfiles/2.dat";
        inf[0]=2;
        inf[1]=2;
        inf[2]=2;
        w=new float**[1];
        w[0]=new float*[2];
        w[0][0]=new float[3];
        w[0][1]=new float[3];
        w[0][0][0]=1;
        w[0][0][1]=2;
        w[0][0][2]=3;
        w[0][1][0]=4;
        w[0][1][1]=5;
        w[0][1][2]=6;
        Restruct(s, w, inf);
        W=getW(s);
        TS_ASSERT_EQUALS(W[0][0][0],w[0][0][0]);
        TS_ASSERT_EQUALS(W[0][0][1],w[0][0][1]);
        TS_ASSERT_EQUALS(W[0][0][2],w[0][0][2]);
        TS_ASSERT_EQUALS(W[0][1][0],w[0][1][0]);
        TS_ASSERT_EQUALS(W[0][1][1],w[0][1][1]);
        TS_ASSERT_EQUALS(W[0][1][2],w[0][1][2]);
    }
};
