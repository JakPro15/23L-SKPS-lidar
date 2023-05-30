CC = gcc
CFLAGS = -O3 -Wall -Werror -Wextra -Wpedantic
LDFLAGS = -lSDL2 -lm

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

TARGET = visual

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.depend: $(SRC)
	$(CC) $(CFLAGS) -MM $^ > $@

include .depend

clean:
	rm -f $(TARGET) *.o
