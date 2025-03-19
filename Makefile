CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99
SRC = src/matrix.c src/int_matrix.c src/float_matrix.c src/double_matrix.c src/main.c
OBJ = $(SRC:.c=.o)
EXEC = matrix_program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)