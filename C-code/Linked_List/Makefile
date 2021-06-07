CC=gcc
CFLAGS= -ansi -pedantic-errors -Wall -Werror -fstack-protector -Wshadow -g

all: public01.x public02.x public03.x public04.x public05.x public06.x \
public07.x public08.x public09.x public10.x

run all: all
	public01.x
	public02.x
	public03.x
	public04.x
	public05.x
	public06.x
	public07.x
	public08.x
	public09.x
	public10.x

public01.x: public01.o list.o
	$(CC) public01.o list.o -o public01.x -g

public02.x: public02.o list.o
	$(CC) public02.o list.o -o public02.x -g

public03.x: public03.o list.o
	$(CC) public03.o list.o -o public03.x -g

public04.x: public04.o list.o
	$(CC) public04.o list.o -o public04.x -g

public05.x: public05.o list.o
	$(CC) public05.o list.o -o public05.x -g

public06.x: public06.o list.o
	$(CC) public06.o list.o -o public06.x -g

public07.x: public07.o list.o
	$(CC) public07.o list.o -o public07.x -g

public08.x: public08.o list.o
	$(CC) public08.o list.o -o public08.x -g

public09.x: public09.o list.o
	$(CC) public09.o list.o -o public09.x -g

public10.x: public10.o list.o
	$(CC) public10.o list.o -o public10.x -g

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

public01.o: public01.c
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c
	$(CC) $(CFLAGS) -c public10.c

clean:
	rm -f *.x *.o
