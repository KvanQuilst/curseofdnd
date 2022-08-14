PROGRAM := dnd
CC      := gcc
CFLAGS  := -g -Wall
LFLAGS  := -ljson-c -lpanel `ncursesw6-config --cflags --libs`

${PROGRAM}: dnd.o draw.o home.o sheet.o load.o log.c char.c
	$(CC) $(LFLAGS) -o ${PROGRAM} $^

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY clean:
clean:
	@rm -rf dnd *.o
