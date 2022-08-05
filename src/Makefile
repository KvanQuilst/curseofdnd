CC      := gcc
CFLAGS  := -g #-Wall
LFLAGS  := -ljson-c -lpanel `ncursesw6-config --cflags --libs`

dnd: dnd.c home.c sea.c load.c
	$(CC) $(CFLAGS) -o dnd dnd.c home.c sea.c load.c -D _XOPEN_SOURCE_EXTENDED $(LFLAGS) 
