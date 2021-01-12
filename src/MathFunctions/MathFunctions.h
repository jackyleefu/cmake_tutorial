#ifndef _MATHFUNCTIONS_H
#define _MATHFUNCTIONS_H

#include <stdbool.h>
#include "TutorialConfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

  DLL_EXPORT double mysqrt(double x);
  // 九九乘法口诀表
  DLL_EXPORT void print_nnmf();
  DLL_EXPORT void print_fibonacci(int number);
  DLL_EXPORT void print_fibonacci2(int maxValue);

  DLL_EXPORT void isLeapyear(int year, bool *result);

  DLL_EXPORT void digits(long long number, int *result);

  DLL_EXPORT void swap(void *p1, void *p2, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* _MATHFUNCTIONS_H */