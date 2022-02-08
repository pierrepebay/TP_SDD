CC=gcc

LDFLAG=$(shell sdl2-config --cflags --libs) -Wall
CFLAG=-Wall $(shell sdl2-config --cflags --libs)
EXEC=res
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAG)

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAG)

.PHONY:clean

clean:
	rm -rf *.o