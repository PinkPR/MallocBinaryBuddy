CC= clang
CFLAGS= -std=c99 -Wall -Wextra -pedantic -g
SRC= $(addprefix src/, malloc.c utils.c free.c calloc.c realloc.c)
TARGET= malloc

all: $(TARGET)

obj: $(SRC)
	$(CC) $(CFLAGS) -fpic -c $(SRC)

lib: obj
	$(CC) -dynamiclib *.o -o libmalloc.so

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).core *.o *.so
