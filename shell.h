
#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

void signal_handler(int sig);
void pary(char ** strings);
char * toString(char ** args);
char ** toAry(char * args);
char * strip(char *s);
int isEmpty(char * x);
int contains(char * str, char * sub);
int help(char ** ary, char * hey);
int contains_ary(char ** ary, char ** hey);
int sizeary(char ** x);
char *str_replace( char *s, const char *oldW, const char *newW);
char * remove_consec_ws(char * x);
char ** subarr(int start, int  division, char ** args);
char *** sep_symbol_cmd(char ** items,char * symbol);
void pipes(char ***args);
void execute_redirect(char ** cmd, char ** files,  char ** direction);
void redirect(char ** args);
void cmd_check(char ** args);

#endif
