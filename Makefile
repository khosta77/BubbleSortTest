TARGET=./a.out
CC=g++
SRCS=./main.cpp
STD=-std=c++20

all: clean $(TARGET)

$(TARGET):
	$(CC) $(STD) -o $(TARGET) $(SRCS)

build: $(TARGET)

clean:
	rm -rf $(TARGET)
