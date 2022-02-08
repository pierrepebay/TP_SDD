CC=gcc

CFLAG=-Wall
EXEC=res
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC):$(OBJ)
	$(CC) -o $@ $^ 

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAG)

.PHONY:clean

clean:
	rm -rf *.o
	rm -rf $(EXEC)