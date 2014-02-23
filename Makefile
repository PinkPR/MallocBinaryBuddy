CC= clang
CFLAGS= -std=c99 -Wall -Wextra -pedantic -g
SRC= $(addprefix src/, main.c malloc.c utils.c free.c)
TARGET= malloc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).core
