#include "s21_cat.h"

void printFile(int argc, char **argv, flag conf) {
  int currentFile = optind;
  FILE *fp;
  int lineNumber = 1;
  while (currentFile != argc) {
    fp = fopen(argv[currentFile], "r");
    if (fp) {
      char ch;
      char temp[2] = {0};
      int execFlagS = 0;
      int firstString = 0;
      while ((ch = getc(fp)) != EOF) {
        temp[0] = temp[1];
        temp[1] = ch;
        // флаг -s сжимает несколько смежных пустых строк
        if (flagS(conf, firstString, currentFile, &execFlagS, temp)) continue;
        // флаг -b нумерует только непустые строки, отменяет -n
        flagB(conf, &firstString, currentFile, temp, &lineNumber);
        // флаг -n нумерует все выходные строки
        flagN(conf, &firstString, currentFile, temp, &lineNumber);
        // флаг -v показывает непечатаемые символы, кроме табуляции и конца
        // строки
        if (flagV(conf, ch)) continue;
        // флаг -е отображает символы конца строки как $ (предполагает и -v)
        flagE(conf, ch);
        // флаг -t показывает непечатаемые символы, кроме конца строки и
        // показывать символы табуляции как ^I
        if (flagT(conf, ch)) continue;
        printf("%c", ch);
        firstString = 1;
      }
      fclose(fp);
    } else {
      fprintf(stderr, "cat: %s: No such file or directory\n",
              argv[currentFile]);
    }
    currentFile++;
  }
}

int flagS(flag conf, int firstString, int currentFile, int *execFlagS,
          char *temp) {
  int toContinue = 0;
  if (conf.flag_s) {
    if (((firstString == 0 && currentFile == optind) ||
         (temp[0] == '\n' && !(*execFlagS))) &&
        temp[1] == '\n')
      *execFlagS = 1;
    else if (temp[1] != '\n')
      *execFlagS = 0;
    else if (*execFlagS)
      toContinue = 1;
  }
  return toContinue;
}

void flagB(flag conf, int *firstString, int currentFile, char *temp,
           int *lineNumber) {
  if (conf.flag_b) {
    if (((*firstString == 0 && currentFile == optind) || temp[0] == '\n') &&
        temp[1] != '\n') {
      printf("%6d\t", (*lineNumber)++);
      *firstString = 1;
    }
  }
}

void flagN(flag conf, int *firstString, int currentFile, char *temp,
           int *lineNumber) {
  if (conf.flag_n && !conf.flag_b) {
    if ((*firstString == 0 && currentFile == optind) || temp[0] == '\n') {
      printf("%6d\t", (*lineNumber)++);
      *firstString = 1;
    }
  }
}

int flagV(flag conf, char ch) {
  int toContinue = 0;
  if (conf.flag_v) {
    if (ch >= 0 && ch < 32 && ch != 9 && ch != 10) {
      printf("^%c", ch + 64);
      toContinue = 1;
    } else if (ch == 127) {
      printf("^?");
      toContinue = 1;
    }
  }
  return toContinue;
}

void flagE(flag conf, char ch) {
  if (conf.flag_e) {
    if (ch == '\n') printf("$");
  }
}

int flagT(flag conf, char ch) {
  int toContinue = 0;
  if (conf.flag_t) {
    if (ch == '\t') {
      printf("^I");
      toContinue = 1;
    }
  }
  return toContinue;
}
