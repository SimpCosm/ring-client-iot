CC = g++
CXXFLAGS := -I/Users/weihoumin/ring-daemon-master/src/ \
            -L/Users/weihoumin/ring-daemon-master/src/.libs/ \
            -Wall -std=c++11 
LIBS := -lring 

all: ring-iot

ring-iot: main.cpp
	$(CC) -o ring-iot main.cpp $(CXXFLAGS) $(LIBS)

clean:
	rm -f *~ *.o ring-iot

