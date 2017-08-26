SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CC = gcc
EXEC = shell

all:$(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) -c $<

#.PHONY: clean
clean:
	rm -f $(OBJ) $(EXEC)