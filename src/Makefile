CC      := gcc
CFLAGS  := -g -Wall
LFLAGS  := -lncursesw

dnd: dnd.c skills.c
	$(CC) $(CFLAGS) $(LFLAGS) -o dnd dnd.c skills.c -D _XOPEN_SOURCE_EXTENDED
