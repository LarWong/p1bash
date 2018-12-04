# Project: p1bash
# shell by Jason Tung and Larry Wong

## Features:

* Forks and executes commands

* Parses multiple commands on one line (ie handles ```;```)

* Redirects using ```<```, ```>```, multiple redirects work also (such as ```cmd < foo > goo```

* Piping and Multi-Piping (```cmd | cmd | cmd | ... ```)

* Handles excess whitespace in commands

* Current Work Directory is printed on every command line

* Can change directories

* Can exit wiht ```exit``` command

* Catches ```Ctrl-C```

## Attempted but Failed:

* Allow user to combine pipes and redirections (such as ```cmd1 < foo | cmd2```

* Shell History and the ```up-arrow``` functionality in regular bash

* Other types of redirect ```>>,<<,2>,etc...```

## Bugs and Issues:

* ```Ctrl-D``` prints current work directory to the command line

* When redirecting a file as ```stdin```, current work directory prints out many times when using '''exit'''

* Cannot deal with tabs in command input

* Inputs and arguments are limited

* Commands need to be separated by spaces (```ls | wc``` works, but ```ls|wc``` does not)

* When the terminal window is made smaller (using mouse) and it causes the text in the terminal to move, user cannot backspace anymore, even when window is restored to the original size.

* Functional, but leaks memory

## Function Headers:

```

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

//Args: int signal_number
//Return: void
//Description: takes care of how the program deals with signals
void signal_handler(int sig);

//Args: char** string_array
//Return: void
//Description: prints an array of strings
void pary(char ** strings);

//Args: char** string_array
//Return: char * long_string
//Description: converts a string array to a single string of all elements
char * toString(char ** args);

//Args: char * long_string
//Return: char** string_array
//Description: splits a long string by spaces and converts it into an array of each substring
char ** toAry(char * args);

//Args: char * string
//Return: char * stripped_string
//Description: strips a string of leading and trailing whitespace
char * strip(char *s);

//Args: char * string
//Return: int boolean
//Description: return if the string is only spaces
int isEmpty(char * x);

//Args: char * string, char * sub_string
//Return: int boolean
//Description: return whether the sub_string is in the string
int contains(char * str, char * sub);

//Args: char ** str_ary, char * str
//Return: int boolean
//Description: return whether the string is in the array
int help(char ** ary, char * hey);

//Args: char ** ary, char ** matching_array
//Return: int boolean
//Description: return index where array elements match, -1 if they never match
int contains_ary(char ** ary, char ** hey);

//Args: char ** array_strings
//Return: int len
//Description: returns size of array of strings
int sizeary(char ** x);

//Args: char* original_str, char* target, char* replace
//Return:
//Description: replaces substrings in the original string with the replace string
char *str_replace( char *s, const char *oldW, const char *newW);

//Args: char* string
//Return: char* filtered_string
//Description: removes consecutive whitespace in a string
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

```

