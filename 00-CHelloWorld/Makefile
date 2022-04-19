
all: hello.exe

run: hello.exe
	./hello-make.exe

hello.exe: hello.o 
	gcc hello.o -o hello-make.exe

hello.o: hello.c
	gcc -c hello.c -std=c18

clean: 
	del hello.o
	del hello-make.exe



# IMPORTANT NOTE: NEVER LEAVE A SPACE AFTER THE * BECAUSE IT'LL DELETE ALL YOUR FILES