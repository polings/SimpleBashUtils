#include "s21_grep.h"

int parseParam(int argc, char **argv, Flag *conf, char *patterns[],
               int *patternsCount, char *patternFiles[],
               int *patternFilesCount) {
  int opt, option_index;
  int error = 0;
  char *short_options = "e:viclnhsf:o";
  struct option long_options[] = {{0, no_argument, NULL, 0}};
  while ((opt = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'e':
        conf->flag_e = 1;
        patterns[*patternsCount] = optarg;
        (*patternsCount)++;
        break;
      case 'c':
        conf->flag_c = 1;
        break;
      case 'n':
        conf->flag_n = 1;
        break;
      case 'i':
        conf->flag_i = 1;
        break;
      case 'l':
        conf->flag_l = 1;
        break;
      case 'v':
        conf->flag_v = 1;
        break;
      case 'h':
        conf->flag_h = 1;
        break;
      case 'o':
        conf->flag_o = 1;
        break;
      case 's':
        conf->flag_s = 1;
        break;
      case 'f':
        conf->flag_f = 1;
        patternFiles[*patternFilesCount] = optarg;
        (*patternFilesCount)++;
        break;
      case '?':
        error = 1;
        fprintf(stderr,
                "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' "
                "for more information.\n");
        exit(1);
    }
    option_index = -1;
  }
  if (conf->flag_e == 0 && argv[optind] != NULL && conf->flag_f == 0) {
    patterns[*patternsCount] = argv[optind];
    (*patternsCount)++;
  }
  return error = noPatternsCheck(patternsCount, patternFilesCount, *conf) ||
                 noPatternFileCheck(patternFilesCount, *patternFiles, *conf) ||
                 error;
}

int noPatternsCheck(int *patternsCount, int *patternFilesCount, Flag conf) {
  int error = 0;
  if (!*patternsCount && !*patternFilesCount) {
    if (!conf.flag_s)
      fprintf(stderr,
              "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' "
              "for more information.\n");
    error = 1;
  }
  return error;
}

int noPatternFileCheck(int *patternFilesCount, char patternFiles[], Flag conf) {
  int error = 0;
  for (int i = 0; i < *patternFilesCount; i++) {
    FILE *file = NULL;
    file = fopen(&patternFiles[i], "r");
    if (file == NULL) {
      if (!conf.flag_s)
        fprintf(stderr, "grep: %s: No such file or directory\n",
                &patternFiles[i]);
      error = 1;
    } else {
      fclose(file);
    }
  }
  return error;
}
