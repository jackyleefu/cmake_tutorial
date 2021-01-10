#if defined(_WIN32)
  #if defined(EXPORTING_MYMATH)
    #define DllExport __declspec(dllexport)
  #else
    // #define DECLSPEC __declspec(dllimport)
    #define DllExport
  #endif
#else // non windows
  #define DllExport
#endif

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

DllExport double mysqrt(double x);
// 九九乘法口诀表
DllExport void print_nnmf();
DllExport void print_fibonacci(int number);
DllExport void print_fibonacci2(int maxValue);

DllExport void isLeapyear(int year, bool *result);

DllExport void digits(long long number, int *result);

DllExport void swap(void *p1, void *p2, size_t size);