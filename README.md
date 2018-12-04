# Project: p1bash
# shell by Jason Tung and Larry Wong

## Features:

* Forks and executes commands

* Parses multiple commands on one line (ie handles ';')

* Redirects using ```<```, ```>```, multiple redirects work also (such as '''cmd < foo > goo'''

* Piping and Multi-Piping ('''cmd | cmd | cmd | ... ''')

* Handles excess whitespace in commands

* Current Work Directory is printed on every command line

* Can change directories

* Catches ```Ctrl-C```

## Attempted but Failed:

* Allow user to combine pipes and redirections (such as '''cmd1 < foo | cmd2'''

* Shell History and the '''up-arrow''' functionality in regular bash

* Other types of redirect '''>>,<<,2>,etc...'''

## Bugs and Issues:

* ```Ctrl-D``` prints current work directory to the command line

* When redirecting a file as ```stdin```, current work directory prints out many times when using '''exit'''

* Cannot deal with tabs in command input

* Inputs and arguments are limited

* Commands need to be separated by spaces ('''ls | wc''' works, but '''ls|wc''' does not)

* When the terminal window is made smaller (using mouse) and it causes the text in the terminal to move, user cannot backspace anymore 9even when window is restored to the original size.

## Files and Function Headers:
