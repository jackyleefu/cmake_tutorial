
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
    // printf("%d, ", t1); // 此处打印开始的数为0:
    nextTerm = t1 + t2;
    t1 = t2;
    t2 = nextTerm;
    printf("%d, ", t1);  // 此处打印开始的数为1:
  }
  printf("\n");
}

// 指定打印小于maxValue前的斐波那契数列
void print_fibonacci2(int maxValue)
{
  int t1 = 0, t2 = 1, nextTerm = 0;

  // 显示前两项,以0起始
  // printf("限制最大值的斐波那契数列: %d, %d, ", t1, t2);
  // 显示前两项,以1起始
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