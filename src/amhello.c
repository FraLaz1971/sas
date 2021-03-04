//~/amhello % cat src/amhello.c
#include <config.h>
#include <stdio.h>
#include "amhellofunc.h"
//#define PACKAGE_STRING "2.0"
int main (void)
{
  puts ("Hello World!");
  printf ("This is %s.\n", PACKAGE_STRING);
// call a function in another file
  myPrintHelloAM();

  return 0;
}
