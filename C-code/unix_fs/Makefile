#Manuel Iribarren 114751782 CMSC216 0204 Project #9 Thursday, November 7th, 2019
#unix.c program Makefile, compiles tests for simulated unix filesystem program
CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Werror -fstack-protector -Wshadow -g

all: public01.x public02.x public03.x public04.x public05.x public06.x \
public07.x public08.x public09.x public10.x

#Runs all public tests and compares their output
run: all
	public01.x < public01.input | diff - public01.output
	public02.x | diff - public02.output
	public03.x | diff - public03.output
	public04.x | diff - public04.output
	public05.x < public05.input | diff - public05.output
	public06.x | diff - public06.output
	public07.x | diff - public07.output
	public08.x | diff - public08.output
	public09.x < public09.input | diff - public09.output
	public10.x < public10.input | diff - public10.output

public01.x: public01.o unix.o driver.o
	$(CC) public01.o unix.o driver.o -o public01.x -g

public02.x: public02.o unix.o
	$(CC) public02.o unix.o -o public02.x -g

public03.x: public03.o unix.o memory-checking.o
	$(CC) public03.o unix.o memory-checking.o -o public03.x -g

public04.x: public04.o unix.o memory-checking.o
	$(CC) public04.o unix.o memory-checking.o -o public04.x -g

public05.x: public05.o unix.o driver.o memory-checking.o
	$(CC) public05.o unix.o driver.o memory-checking.o -o public05.x -g

public06.x: public06.o unix.o
	$(CC) public06.o unix.o -o public06.x -g

public07.x: public07.o unix.o
	$(CC) public07.o unix.o -o public07.x -g

public08.x: public08.o unix.o
	$(CC) public08.o unix.o -o public08.x -g

public09.x: public09.o unix.o driver.o
	$(CC) public09.o unix.o driver.o -o public09.x -g

public10.x: public10.o unix.o driver.o
	$(CC) public10.o unix.o driver.o -o public10.x -g

unix.o: unix.c unix.h
	$(CC) $(CFLAGS) -c unix.c

public01.o: public01.c unix.h driver.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c unix.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c unix.h memory-checking.h
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c unix.h memory-checking.h
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c unix.h driver.h memory-checking.h
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c unix.h
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c unix.h
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c unix.h
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c unix.h driver.h
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c unix.h driver.h
	$(CC) $(CFLAGS) -c public10.c

clean:
	rm -f *.x public*.o
