#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "MathFunctions.h"
#include "TutorialConfig.h"
#include "parseOpt.h"

// 定义一个无参数的函数指针类型
typedef int (*Fn1)(void);
// 定义一个有参数的函数指针类型
typedef void (*Fn2)(int);

// 定义一个Book结构类型
typedef struct
{
  char title[50];
  char author[50];
  char subject[100];
  int book_id;
  Fn2 callback;
} Book;

// 定义一个处理结构体的函数
void printBook(Book *book)
{
  // 结构体指针需要使用`->`访问结构体成员
  printf("结构体成员:\n书名: %s\n作者: %s\n类别: %s\n编号: %d\n", book->title, book->author, book->subject, book->book_id);
  book->callback(2);
}

// 定义一个函数, 获取随机值
int getNextRandomValue(void)
{
  return rand();
}

// 一个带回调函数参数的函数, 填充数组
void populate_array(int *array, size_t arraySize, Fn1 getNextValue)
{
  for (size_t i = 0; i < arraySize; i++)
  {
    array[i] = getNextValue();
  }
}

void cb(int x)
{
  printf("结构体函数成员调用了\n");
};

// 二级指针用法
void my_malloc(char **s)
{
  *s = (char *)malloc(100 * sizeof(char));
}

int main(int argc, char *argv[])
{
#ifdef _WIN32
  setlocale(LC_ALL, "");
#else
  setlocale(LC_ALL, "en_US.utf8");
#endif

  // 解析命令参数
  char *optStr = "vi:o:f:h";
  char *usageFtm = "%s [-v] [-f hexflag] [-i inputfile] [-o outputfile] [-h]";
  parse_opt(argc, argv, optStr, usageFtm);

  // 例1: 查看当前系统各整型类型的字节长度
  printf("当前系统基本类型的字节长度: char %zd, short %zd, int %zd, long %zd, long long %zd, float %zd, double %zd, long double %zd \n", sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(long long), sizeof(float), sizeof(double), sizeof(long double));

  // 例2: 输出字符的十六进制值.
  char a = 'z';
  printf("字符z的十六进制数: %#x \n", a);

  // 例3: 字符串转数字
  const char *str = "123abc";
  long long num = strtoll(str, NULL, 0);
  printf("字符串\"%s\"转整型: %lld \n", str, num);
  double dd = strtod(str, NULL);
  printf("字符串\"%s\"转浮点型: %lf \n", str, dd);

  // 例4: 函数指针的使用
  int myarray[10];
  size_t arrlength = sizeof(myarray) / sizeof(int);
  populate_array(myarray, arrlength, getNextRandomValue);
  printf("数组长度:%zd \n", arrlength);
  for (size_t i = 0; i < arrlength; i++)
  {
    printf("%d, ", myarray[i]);
  }
  printf("\n");

  // 例4: 结构体的使用
  Book book = {"C语言", "Fzw", "编程语言", 123456, cb};
  printBook(&book);

  // 例5: 使用链接库中的成员.
  double result = mysqrt(25);
  printf("链接库的函数调用结果:%.2f \n", result);

  // 例6: 指针地址
  int b = 1;
  int *p1 = &b;
  int *p2 = p1;
  printf("当前系统指针的字节长度: %zd \n", sizeof(void *));
  printf("c中所有都是值传递的.b的地址:%p,p1地址:%p, p2地址:%p \n", &b, &p1, &p2);

  // 例7: 二级指针用法
  char *p3 = NULL;
  my_malloc(&p3); // 取指针变量的地址, 为p3在堆上分配内存空间
  strcpy(p3, "这是在内存堆上的字符串");
  puts(p3);
  if (p3)
  {
    free(p3);
  }

  // 例8: 输出九九乘法口诀表
  print_nnmf();
  print_fibonacci(10);
  print_fibonacci2(100);

  // 例9: 判断是否是闰年
  int year = 2021;
  bool leapyear = false;
  isLeapyear(year, &leapyear);
  if (leapyear)
  {
    printf("%d年是闰年\n", year);
  }
  else
  {
    printf("%d年不是闰年\n", year);
  }

  int number = 123456789;
  int digitNum = 0;
  digits(number, &digitNum);
  printf("%d是%d位数字\n", number, digitNum);

  // 例10: 模拟泛型编程
  int a1 = 1, b1 = 2;
  printf("交换前a=%d,b=%d", a1, b1);
  swap(&a1, &b1, sizeof(int));
  printf("交换后a=%d,b=%d\n", a1, b1);

  char *a2 = "aaaa";
  char *b2 = "bbb";

  printf("交换前a=%s,b=%s", a2, b2);
  swap(&a2, &b2, sizeof(void *));
  printf("交换后a=%s,b=%s\n", a2, b2);

  // 命令行暂停等待用户按任意键后退出.
  // system("pause");
  return 0;
}