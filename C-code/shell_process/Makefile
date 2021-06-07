CC= gcc
CFLAGS= -ansi -pedantic-errors -Wall -Werror -fstack-protector -Wshadow -g

all: xargs.x

run:
		public01 | diff - public01.output
		public02 | diff - public02.output
		public03 | diff - public03.output
		public04 | diff - public04.output
		public05 | diff - public05.output
		public06 | diff - public06.output
		public07 | diff - public07.output
		public08 | diff - public08.output
		public09 | diff - public09.output

		public10 | diff - public10.output
		public11 | diff - public11.output
		public12 | diff - public12.output
		public13 | diff - public13.output
		public14 | diff - public14.output
		public15 | diff - public15.output
		public16 | diff - public16.output
		public17 | diff - public17.output
		public18 | diff - public18.output
		public19 | diff - public19.output


xargs.x: xargs.o safe-fork.o split.o
	$(CC) xargs.o safe-fork.o split.o -o xargs.x

xargs.o: xargs.c safe-fork.h split.h
	$(CC) $(CFLAGS) -c xargs.c
