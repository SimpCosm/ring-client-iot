CC = g++
CFLAGS := -Wall -std=c++11 -lring -L /home/houmin/ring-daemon/src/.libs -static

all: ring-iot

ring-iot: main.cpp
	$(CC) -o ring-iot main.cpp $(CFLAGS)

clean:
	rm -f *~ *.o ring-iot

