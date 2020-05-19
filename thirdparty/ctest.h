#include "input.h"
#include "learn.h"
#include "network.h"
#include <cxxtest/TestSuite.h>
#include <iostream>
using namespace std;
const int n = 5;

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

};
