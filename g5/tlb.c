#include <stdio.h>

#define ASIZE 2000000
#define ITERATIONS 1000000000
#define PAGESIZE 4096

int main()
{
   int a[ASIZE];
   int jump = PAGESIZE/sizeof(int);
   printf("NUMPAGES: %d", NUMPAGES);
   for (int j = 0; j < ITERATIONS/NUMPAGES; j++)
      for (int i =0; i < NUMPAGES*jump; i += jump) {
         a[i] += 1;
      }
}
