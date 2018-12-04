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

* When the terminal window is made smaller (using mouse) and it causes the text in the terminal to move, user cannot backspace anymore 9even when window is restored to the original size.

## Function Headers:

```
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
```

