
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

//Args: int start,int end,char** mainarr
//Return: char ** subarray
//Description: Returns a subarray of the input array
char ** subarr(int start, int  end, char ** mainarr);

//Args: char** items,char* symbol
//Return: char *** array_of_arrays
//Description: Given a string array, it split this array by symbol and returns an array of string arrays
char *** sep_symbol_cmd(char ** items,char * symbol);

//Args: char *** groups_of_commands
//Return: void
//Description: Given an array of commands(in the form of string arrays), it pipes them together
void pipes(char ***args);

//Args: char ** arguments
//Return: void
//Description: Separates arguments into command, files and redirections. Sends them to execute_redirect to be run
void redirect(char ** args);

//Args: char ** commands, char ** files, char ** file_redirections
//Return: void
//Description: Executes the command and redirects in/out to the seperate files
void execute_redirect(char ** cmd, char ** files,  char ** direction);

//Args: char ** args
//Return: void
//Description: Given the arguments, it determines what to do (pipes, redirects, etc...)
void cmd_check(char ** args);

#endif
