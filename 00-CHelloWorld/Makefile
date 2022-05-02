all: 00-CHelloWorld/hello.exe

run: 00-CHelloWorld/hello.exe
	./00-CHelloWorld/hello.exe

00-CHelloWorld/hello.exe: 00-CHelloWorld/hello.o 
	gcc 00-CHelloWorld/hello.o -o 00-CHelloWorld/hello.exe

00-CHelloWorld/hello.o: 00-CHelloWorld/hello.c
	gcc -c 00-CHelloWorld/hello.c -std=c18 -o 00-CHelloWorld/hello.o

clean: 
	del 00-CHelloWorld/hello.o
	del 00-CHelloWorld/hello.exe

# IMPORTANT NOTE: NEVER LEAVE A SPACE AFTER THE * BECAUSE IT'LL DELETE ALL YOUR FILES