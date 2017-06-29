CC = g++
CFLAGS := -Wall -std=c++11 -lring -static

all: ring-iot

ring-iot: main.cpp
	$(CC) -o ring-iot main.cpp $(CFLAGS)

clean:
	rm -f *~ *.o ring-iot

