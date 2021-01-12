
#include "MathFunctions.h"
#ifdef USE_MYMATH
  #include <stdio.h>
#endif

double mysqrt(double x)
{
#ifdef USE_MYMATH
  return x / 2;
#else
  return x / 2 / 2;
#endif
}

// 打印九九乘法口诀表
void print_nnmf()
{
  //外层循环变量,控制行
  int i = 0;
  //内层循环变量,控制列
  int j = 0;
  for (i = 1; i <= 9; i++)
  {
    for (j = 1; j <= i; j++)
    {
      printf("%dx%d=%d\t", j, i, i * j);
    }
    //每行输出完后换行
    printf("\n");
  }
}

// 指定打印多少个斐波那契数列
void print_fibonacci(int number)
{

  int t1 = 0, t2 = 1, nextTerm;
  printf("限制个数的斐波那契数列: ");

  for (int i = 1; i <= number; ++i)
  {
    // printf("%d, ", t1); // 此处打印以0起始
    nextTerm = t1 + t2;
    t1 = t2;
    t2 = nextTerm;
    printf("%d, ", t1); // 此处打印以1起始
  }
  printf("\n");
}

// 指定打印小于maxValue前的斐波那契数列
void print_fibonacci2(int maxValue)
{
  int t1 = 0, t2 = 1, nextTerm = 0;

  // 以0起始先打印前两项
  // printf("限制最大值的斐波那契数列: %d, %d, ", t1, t2);
  // 以1起始先打印前一项
  printf("限制最大值的斐波那契数列: %d, ", t2);

  nextTerm = t1 + t2;

  while (nextTerm <= maxValue)
  {
    printf("%d, ", nextTerm);
    t1 = t2;
    t2 = nextTerm;
    nextTerm = t1 + t2;
  }
  printf("\n");
}

// 判断年份是否是闰年
void isLeapyear(int year, bool *result)
{
  // （非百年,四年一闰) || 逢四百年是闰年
  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
  {
    *result = true;
  }
  else
  {
    *result = false;
  }
}

// 判断输入的整数是几位数.
void digits(long long number, int *result)
{
  int count = 0;
  while (number != 0)
  {
    // 得到商
    number /= 10;
    ++count;
  }

  *result = count;
}

// 模拟泛型编程
void swap(void *p1, void *p2, size_t size)
{
  void *temp = malloc(size);
  memcpy(temp, p1, size);
  memcpy(p1, p2, size);
  memcpy(p2, temp, size);
  free(temp);
}