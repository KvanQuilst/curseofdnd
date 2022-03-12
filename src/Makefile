CC      := gcc
CFLAGS  := -g -Wall
LFLAGS  := `ncursesw6-config --cflags --libs`

dnd: dnd.c logo.c skills.c health.c attack.c sea.c
	$(CC) $(CFLAGS) $(LFLAGS) -o dnd dnd.c logo.c skills.c health.c attack.c sea.c -D _XOPEN_SOURCE_EXTENDED
