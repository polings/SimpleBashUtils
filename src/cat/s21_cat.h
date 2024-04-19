#ifndef SRC_CAT_S21_CAT_H_H
#define SRC_CAT_S21_CAT_H_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flag {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_v;
} flag;

int parseParam(int argc, char **argv, flag *conf);
void printFile(int argc, char **argv, flag conf);
int flagS(flag conf, int firstString, int currentFile, int *execFlagS,
          char *temp);
void flagB(flag conf, int *firstString, int currentFile, char *temp,
           int *lineNumber);
void flagN(flag conf, int *firstString, int currentFile, char *temp,
           int *lineNumber);
int flagV(flag conf, char ch);
void flagE(flag conf, char ch);
int flagT(flag conf, char ch);

#endif  // SRC_CAT_S21_CAT_H_H
