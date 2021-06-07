CFLAGS= -ansi -pedantic-errors -Wall -Werror -fstack-protector -Wshadow -g

all: public01.x public02.x public03.x public04.x public05.x public06.x public07.x \
	public08.x public09.x public10.x secret01.x secret02.x secret03.x secret04.x \
	secret05.x secret06.x secret07.x secret08.x secret09.x secret10.x secret11.x \
	secret12.x secret13.x secret14.x secret15.x secret16.x secret17.x secret18.x

public01.x: public01.o machine.o
	$(CC) public01.o machine.o -o public01.x -g

public02.x: public02.o machine.o
	$(CC) public02.o machine.o -o public02.x -g

public03.x: public03.o machine.o
	$(CC) public03.o machine.o -o public03.x -g

public04.x: public04.o machine.o
	$(CC) public04.o machine.o -o public04.x -g

public05.x: public05.o machine.o
	$(CC) public05.o machine.o -o public05.x -g

public06.x: public06.o machine.o
	$(CC) public06.o machine.o -o public06.x -g

public07.x: public07.o machine.o
	$(CC) public07.o machine.o -o public07.x -g

public08.x: public08.o machine.o
	$(CC) public08.o machine.o -o public08.x -g

public09.x: public09.o machine.o
	$(CC) public09.o machine.o -o public09.x -g

public10.x: public10.o machine.o
	$(CC) public10.o machine.o -o public10.x -g

secret01.x: secret01.o machine.o
	$(CC) secret01.o machine.o -o secret01.x -g

secret02.x: secret02.o machine.o
	$(CC) secret02.o machine.o -o secret02.x -g

secret03.x: secret03.o machine.o
	$(CC) secret03.o machine.o -o secret03.x -g

secret04.x: secret04.o machine.o
	$(CC) secret04.o machine.o -o secret04.x -g

secret05.x: secret05.o machine.o
	$(CC) secret05.o machine.o -o secret05.x -g

secret06.x: secret06.o machine.o
	$(CC) secret06.o machine.o -o secret06.x -g

secret07.x: secret07.o machine.o
	$(CC) secret07.o machine.o -o secret07.x -g

secret08.x: secret08.o machine.o
	$(CC) secret08.o machine.o -o secret08.x -g

secret09.x: secret09.o machine.o
	$(CC) secret09.o machine.o -o secret09.x -g

secret10.x: secret10.o machine.o
	$(CC) secret10.o machine.o -o secret10.x -g

secret11.x: secret11.o machine.o
	$(CC) secret11.o machine.o -o secret11.x -g

secret12.x: secret12.o machine.o
	$(CC) secret12.o machine.o -o secret12.x -g

secret13.x: secret13.o machine.o
	$(CC) secret13.o machine.o -o secret13.x -g

secret14.x: secret14.o machine.o
	$(CC) secret14.o machine.o -o secret14.x -g

secret15.x: secret15.o machine.o
	$(CC) secret15.o machine.o -o secret15.x -g

secret16.x: secret16.o machine.o
	$(CC) secret16.o machine.o -o secret16.x -g

secret17.x: secret17.o machine.o
	$(CC) secret17.o machine.o -o secret17.x -g

secret18.x: secret18.o machine.o
	$(CC) secret18.o machine.o -o secret18.x -g

machine.o: machine.c machine.h
	$(CC) $(CFLAGS) -c machine.c

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

secret01.o: secret01.c
	$(CC) $(CFLAGS) -c secret01.c

secret02.o: secret02.c
	$(CC) $(CFLAGS) -c secret02.c

secret03.o: secret03.c
	$(CC) $(CFLAGS) -c secret03.c

secret04.o: secret04.c
	$(CC) $(CFLAGS) -c secret04.c

secret05.o: secret05.c
	$(CC) $(CFLAGS) -c secret05.c

secret06.o: secret06.c
	$(CC) $(CFLAGS) -c secret06.c

secret07.o: secret07.c
	$(CC) $(CFLAGS) -c secret07.c

secret08.o: secret08.c
	$(CC) $(CFLAGS) -c secret08.c

secret09.o: secret09.c
	$(CC) $(CFLAGS) -c secret09.c

secret10.o: secret10.c
	$(CC) $(CFLAGS) -c secret10.c

secret11.o: secret11.c
	$(CC) $(CFLAGS) -c secret11.c

secret12.o: secret12.c
	$(CC) $(CFLAGS) -c secret12.c
secret13.o: secret13.c
	$(CC) $(CFLAGS) -c secret13.c

secret14.o: secret14.c
	$(CC) $(CFLAGS) -c secret14.c

secret15.o: secret15.c
	$(CC) $(CFLAGS) -c secret15.c

secret16.o: secret16.c
	$(CC) $(CFLAGS) -c secret16.c

secret17.o: secret17.c
	$(CC) $(CFLAGS) -c secret17.c

secret18.o: secret18.c
	$(CC) $(CFLAGS) -c secret18.c

clean:
	rm -f *.x *.o
