CC = gcc
CFLAGS = -Wall -Wextra -Werror

TARGET = db
SRC = main.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
