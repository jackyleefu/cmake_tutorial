#if defined(_WIN32)
#  if defined(EXPORTING_MYMATH)
#    define DllExport __declspec(dllexport)
#  else
// #    define DECLSPEC __declspec(dllimport)
#    define DllExport
#  endif
#else // non windows
#  define DllExport
#endif

DllExport double mysqrt(double x);
