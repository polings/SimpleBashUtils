#include "s21_grep.h"

void printFile(int argc, char **argv, Flag conf, char *patterns[],
               int patternsCount, char *patternFiles[], int patternFilesCount) {
  int fileCount = 0;
  int currentFile =
      (conf.flag_e == 1 || conf.flag_f == 1 ? optind : optind + 1);
  int flagForC = argc - currentFile;
  char *fileName;
  FILE *fp;
  while (currentFile != argc) {
    int matchCount = 0;
    fileName = argv[currentFile];
    fp = fopen(fileName, "r");
    if (fp) {
      if (currentFile != (argc - 1)) fileCount++;
      matchCount =
          fileProcessing(fp, conf, patterns, patternsCount, patternFiles,
                         patternFilesCount, fileName, flagForC);
      processingFlagC(conf, matchCount, fileName, flagForC);
      processingFlagL(conf, matchCount, fileName);
      fclose(fp);
    } else if (!conf.flag_s) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n",
              argv[currentFile]);
    }
    currentFile++;
  }
}

int fileProcessing(FILE *file, Flag conf, char *patterns[], int patternsCount,
                   char *patternFiles[], int patternFilesCount, char *fileName,
                   int fileCount) {
  int matchCount = 0;
  ssize_t endOfFile = 0;
  size_t length = 0;
  int lineNumber = 1;

  char *currentLine = NULL;
  while ((endOfFile = getline(&currentLine, &length, file)) != EOF) {
    if (currentLine == NULL) {
      lineNumber++;
      continue;
    }
    int matchFlag = 0;
    char *matchSearch = searchInFile(currentLine, conf, patterns, patternsCount,
                                     patternFiles, patternFilesCount);
    if (matchSearch) {
      matchFlag = 1;
    }
    if ((matchFlag && !conf.flag_v) || (!matchFlag && conf.flag_v)) {
      matchCount++;
      if (!conf.flag_c && !conf.flag_l && !conf.flag_o) {
        printLine(currentLine, lineNumber, conf, fileName, fileCount);
      }
    }
    lineNumber++;
  }
  free(currentLine);
  return matchCount;
}

void printLine(char *currentLine, int lineNumber, Flag conf, char *fileName,
               int fileCount) {
  if (fileCount == 1 || conf.flag_h) {
    if (conf.flag_n)
      fprintf(stdout, "%d:%s", lineNumber, currentLine);
    else
      fprintf(stdout, "%s", currentLine);
  } else {
    if (conf.flag_n)
      fprintf(stdout, "%s:%d:%s", fileName, lineNumber, currentLine);
    else
      fprintf(stdout, "%s:%s", fileName, currentLine);
  }
  if (currentLine[strlen(currentLine) - 1] != '\n') printf("\n");
}

void processingFlagC(Flag conf, int matchCount, char *fileName, int fileCount) {
  if (conf.flag_c && !conf.flag_l) {
    if (fileCount == 1 || conf.flag_h)
      fprintf(stdout, "%d\n", matchCount);
    else
      fprintf(stdout, "%s:%d\n", fileName, matchCount);
  }
}

void processingFlagL(Flag conf, int matchCount, char *fileName) {
  if (conf.flag_l) {
    if (matchCount) printf("%s\n", fileName);
  }
}
