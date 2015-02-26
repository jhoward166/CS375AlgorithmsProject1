CC = gcc


# Specifiy the target
all: program1 program2 program3

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
program1: program1.o
	gcc program1.o -o program1

program2: program2.o
	gcc program2.o -o program2

program3: program3.o
	gcc program3.o -o program3

# Specify how the object files should be created from source files
program1.o: program1.c
	gcc -c  program1.c

program2.o: program2.c
	gcc -c  program2.c

program3.o: program3.c
	gcc -c  program3.c


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

clean:
	rm -f *.o program1 program2 program3 *~
