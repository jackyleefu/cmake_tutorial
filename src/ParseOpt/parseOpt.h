#ifndef _PARSEOPT_H
#define _PARSEOPT_H

#include <stdio.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include "TutorialConfig.h"

#ifdef __cplusplus
extern "C" 
{
#endif 

typedef struct
{
  int verbose;
  uint32_t flags;
  FILE *input;
  FILE *output;
} options_t;

DLL_EXPORT int parse_opt(int argc, char *argv[], char *optStr, char *usageFmt);

DLL_EXPORT void usage(char *progname, int opt, char* usageFmt);

#ifdef __cplusplus
}
#endif 

#endif /* _PARSEOPT_H */