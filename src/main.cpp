#include "input.h"
#include "network.h"
int main()
{
 int *a, kpixel = 0;
 		   a = input("files_bmp/2.bmp", a, &kpixel);
    	printpixel(a, kpixel);
    return 0;
}
