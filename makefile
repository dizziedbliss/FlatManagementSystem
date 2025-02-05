CC = gcc
CFLAGS = -Iincludes -lm
SRCS = src/main.c src/flats.c src/functions.c 
OBJS = build/main.o build/flats.o build/functions.o 
TARGET = build/main 

all: $(TARGET)

build:
	mkdir -p build


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build 

.PHONY: all clean

# ver 3.1.0 stable
