#ifndef SRC_GREP_S21_GREP_H_H
#define SRC_GREP_S21_GREP_H_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flag {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_f;
  int flag_h;
  int flag_s;
  int flag_o;
  int NoSearchString;
} Flag;

// parse.c
int parseParam(int argc, char **argv, Flag *conf, char *patterns[],
               int *patternsCount, char *patternFiles[],
               int *patternFilesCount);
int noPatternsCheck(int *patternsCount, int *patternFilesCount, Flag conf);
int noPatternFileCheck(int *patternFilesCount, char patternFiles[], Flag conf);
// search.c
char *searchPattern(char *sourceLine, char *patterns, Flag conf,
                    regmatch_t *patternMatch);
char *searchInFile(char *sourceLine, Flag conf, char *patterns[],
                   int patternsCount, char *patternFiles[],
                   int patternFilesCount);
// print.c
void printFile(int argc, char **argv, Flag conf, char *patterns[],
               int patternsCount, char *patternFiles[], int patternFilesCount);
int fileProcessing(FILE *file, Flag conf, char *patterns[], int patternsCount,
                   char *patternFiles[], int patternFilesCount, char *fileName,
                   int fileCount);
void printLine(char *currentLine, int lineNumber, Flag conf, char *fileName,
               int fileCount);
void processingFlagC(Flag conf, int matchCount, char *fileName, int fileCount);
void processingFlagL(Flag conf, int matchCount, char *fileName);
void processingFlagF(char *patterns[], char *patternFiles[],
                     int *patternsCount);

#endif  // SRC_GREP_S21_GREP_H_H
