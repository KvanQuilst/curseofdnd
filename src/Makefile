CC      := gcc
CFLAGS  := -g -Wall
LFLAGS  := `ncursesw6-config --cflags --libs`

dnd: dnd.c skills.c
	$(CC) $(CFLAGS) $(LFLAGS) -o dnd dnd.c skills.c -D _XOPEN_SOURCE_EXTENDED
