all : shell

shell : shell.o
		gcc -o shell shell.o 

shell.o : shell.c
		gcc -c shell.c

clean :
		rm shell *.o