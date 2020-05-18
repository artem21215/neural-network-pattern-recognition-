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
    void test_getw(void)
    {
        getW(float*** Weight);
    }
};
