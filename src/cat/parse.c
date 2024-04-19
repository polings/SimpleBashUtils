#include "s21_cat.h"

int parseParam(int argc, char **argv, flag *conf) {
  int opt = 0;
  int error = 0;
  int option_index = -1;
  char *short_options = "beEnstTv";
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'}};
  while ((opt = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        conf->flag_b = 1;
        break;
      case 'e':
        conf->flag_e = 1;
        conf->flag_v = 1;
        break;
      case 'E':
        conf->flag_e = 1;
        break;
      case 'n':
        conf->flag_n = 1;
        break;
      case 's':
        conf->flag_s = 1;
        break;
      case 't':
        conf->flag_t = 1;
        conf->flag_v = 1;
        break;
      case 'T':
        conf->flag_t = 1;
        break;
      case 'v':
        conf->flag_v = 1;
        break;
      case '?':
        error = 1;
        break;
    }
    if (error) {
      fprintf(stderr, "Try 'cat --help' for more information.\n");
      break;
    }
    option_index = -1;
  }
  return error;
}
