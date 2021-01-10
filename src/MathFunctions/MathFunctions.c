
#include "MathFunctions.h"
#ifdef USE_MYMATH
#  include <stdio.h>
#endif

double mysqrt(double x)
{
#ifdef USE_MYMATH
  return x / 2;
#else
  return x / 2 / 2;
#endif
}

