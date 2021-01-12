#include <stdlib.h>
#include <string.h>
#include <wchar.h>

size_t characterCount(const char *str){
  // 例11: MBCS 转 WCS
  size_t requiredSize = mbstowcs(NULL, str, 0);                           // 获取MBCS字符串的字节大小
  wchar_t *wcs = (wchar_t *)malloc((requiredSize + 1) * sizeof(wchar_t)); // 堆上创建WCS需要的空间
  size_t size = mbstowcs(wcs, str, requiredSize + 1);                     // MBCS转WCS
  return wcslen(wcs);
}