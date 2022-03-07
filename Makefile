CC=gcc

CFLAG= -Wall -Wextra -g
EXEC=res
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC):$(OBJ)
	$(CC) -o $@ $^
	mv $^ bin/

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAG)

.PHONY:clean

clean:
	rm -rf bin/*.o
	rm -rf $(EXEC)
