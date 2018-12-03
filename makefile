all: main.o shell.o
	gcc -o shell main.o shell.o
main.o: main.c shell.h
	gcc -c main.c shell.h
shell.o: shell.c shell.h
	gcc -c shell.c shell.h
run:
	./shell
clean:
	rm -f shell *.o *~ *.gch
fun:
	echo NORMAL TEST
	ls
	ls -a -l
	echo CD TEST
	cd ..
	pwd
	echo SEMICOLON TEST
	ps ; echo HELLO
	echo STDOUT REDIRECT TEST
	w > wholist
	cat wholist
	echo STDIN REDIRECT TEST
	tr a-z A-Z < wholist
	echo DOUBLE REDIRECT TEST
	tr a-z A-Z < wholist > foo
	cat foo
	echo PIPE TEST
	ls | wc
	rm wholist foo
	echo EXIT
	exit
