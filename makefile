INCLUDE_DIR = ./include

all: compile clean

compile: main.o lexical.o syntax.o
	gcc main.o lexical.o syntax.o -o compile

main.o: main.c
	gcc -c main.c -I $(INCLUDE_DIR)

lexical.o: lexical.c
	gcc -c lexical.c -I $(INCLUDE_DIR)

syntax.o: syntax.c
	gcc -c syntax.c -I $(INCLUDE_DIR)

clean:
	rm.exe -f *.o