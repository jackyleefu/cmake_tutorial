#include "parseOpt.h"

#if defined(_WIN32)
  #include "getopt.h"
  #include <io.h>
  #include <process.h>
#else
  #include <getopt.h>
  #include <unistd.h>
#endif


#define ERR_FOPEN_INPUT "fopen(input, r)"
#define ERR_FOPEN_OUTPUT "fopen(output, w)"
#define ERR_DO_THE_NEEDFUL "do_the_needful blew up"
#define DEFAULT_PROGNAME "command"

int parse_opt(int argc, char *argv[], char *optStr, char *usageFmt)
{
  int opt;
  options_t options = {0, 0x0, stdin, stdout};
  opterr = 0;
  while ((opt = getopt(argc, argv, optStr)) != EOF)
    switch (opt)
    {
    case 'i':
      if (!(options.input = fopen(optarg, "r")))
      {
        perror(ERR_FOPEN_INPUT);
        exit(EXIT_FAILURE);
        /* NOTREACHED */
      }
      break;
    case 'o':
      if (!(options.output = fopen(optarg, "w")))
      {
        perror(ERR_FOPEN_OUTPUT);
        exit(EXIT_FAILURE);
        /* NOTREACHED */
      }
      break;

    case 'f':
      options.flags = (uint32_t)strtoul(optarg, NULL, 16);
      break;
    case 'v':
      options.verbose += 1;
      break;
    case 'h':
    default:
      char fname[_MAX_FNAME];
      _splitpath(argv[0], NULL, NULL, fname, NULL);
      printf_s("%s",fname);
      usage(fname, opt, usageFmt);
      /* NOTREACHED */
      break;
    }
  if (do_the_needful(&options) != EXIT_SUCCESS)
  {
    perror(ERR_DO_THE_NEEDFUL);
    exit(EXIT_FAILURE);
    /* NOTREACHED */
  }
  return EXIT_SUCCESS;
}
void usage(char *progname, int opt, char* usageFmt)
{
  fprintf(stderr, usageFmt, progname ? progname : DEFAULT_PROGNAME);
  exit(EXIT_FAILURE);
  /* NOTREACHED */
}
int do_the_needful(options_t *options)
{
  if (!options)
  {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  if (!options->input || !options->output)
  {
    errno = ENOENT;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}