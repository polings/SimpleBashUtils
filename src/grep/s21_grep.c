#include "s21_grep.h"

int main(int argc, char **argv) {
  Flag flagData = {0};
  char *patterns[100] = {'\0'};
  char *patternFiles[100];
  int patternsCount = 0;
  int patternFilesCount = 0;

  if ((parseParam(argc, argv, &flagData, patterns, &patternsCount, patternFiles,
                  &patternFilesCount) == 0) &&
      (!flagData.flag_v || !flagData.flag_o)) {
    printFile(argc, argv, flagData, patterns, patternsCount, patternFiles,
              patternFilesCount);
  }
  return 0;
}
