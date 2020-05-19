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
};
