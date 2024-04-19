#include "s21_grep.h"

#define _GNU_SOURCE
#include <stdio.h>

char *searchPattern(char *sourceLine, char *patterns, Flag conf,
                    regmatch_t *patternMatch) {
  char *result = NULL;
  if (sourceLine[0] != 0 && ((sourceLine[0] != '\n') || conf.flag_f)) {
    regex_t preg;
    int rc = 0;
    char buffer[100];
    int nmatch = strlen(sourceLine);
    // Компиляция регулярного выражения
    rc =
        regcomp(&preg, patterns,
                (conf.flag_i == 1 ? (REG_EXTENDED | REG_ICASE) : REG_EXTENDED));
    if (rc != 0) {
      regerror(rc, &preg, buffer, 100);
      printf("regcomp() failed with '%s'\n", buffer);
      exit(1);
    }
    // Выполнение скомпилированного регулярного выражения
    if ((rc = regexec(&preg, sourceLine, nmatch, patternMatch, 0)) == 0) {
      result = sourceLine;
    } else if (rc != REG_NOMATCH) {
      printf("failed to ERE match '%s' with '%s',returning %d.\n", sourceLine,
             patterns, rc);
      exit(1);
    }
    // Обработка флага -о
    if (result != NULL && conf.flag_o) {
      for (int i = (int)patternMatch[0].rm_so; i < patternMatch[0].rm_eo; i++) {
        printf("%c", sourceLine[i]);
      }
      printf("\n");
    }
    // Освобождение памяти для регулярного выражения
    regfree(&preg);
  }
  return result;
}

char *searchInFile(char *sourceLine, Flag conf, char *patterns[],
                   int patternsCount, char *patternFiles[],
                   int patternFilesCount) {
  char *result = NULL;
  regmatch_t pmatch[strlen(sourceLine)];
  char *patternInLine = NULL;
  size_t lenLine = 0;
  // Проверка: есть ли совпадение с паттерном в строке
  for (int i = 0; i < patternsCount; i++) {
    result = searchPattern(sourceLine, patterns[i], conf, pmatch);
    if (result != NULL || (result != NULL && conf.flag_v)) {
      break;
    }
  }
  // Если нет совпадений, то проходимся по шаблонным файлам
  if (result == NULL) {
    for (int j = 0; j < patternFilesCount; j++) {
      FILE *file = fopen(patternFiles[j], "r");
      ssize_t line = 0;
      while ((line = getline(&patternInLine, &lenLine, file)) != EOF) {
        if (patternInLine == NULL) {
          continue;
        }
        if (patternInLine[strlen(patternInLine) - 1] == 10 ||
            patternInLine[strlen(patternInLine) - 1] == 13) {
          patternInLine[strlen(patternInLine) - 1] = '\0';
        }
        result = searchPattern(sourceLine, patternInLine, conf, pmatch);
        if ((result != NULL && !conf.flag_o) || (result != NULL && conf.flag_v))
          break;
      }
      free(patternInLine);
      fclose(file);
    }
  }
  return result;
}
