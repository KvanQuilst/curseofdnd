CC      := gcc
CFLAGS  := -g -Wall
LFLAGS  := -lpanel `ncursesw6-config --cflags --libs`

dnd: dnd.c home.c sea.c
	$(CC) $(CFLAGS) $(LFLAGS) -o dnd dnd.c home.c sea.c -D _XOPEN_SOURCE_EXTENDED
