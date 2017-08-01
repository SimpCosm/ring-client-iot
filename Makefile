CC = g++
DAEMON = /Users/weihoumin/ring-daemon-master/src

CXXFLAGS := -I$(DAEMON) \
            -L$(DAEMON)/.libs/ \
            -I. \
			-Wall -std=c++11 
LIBS := -lring 

all: ring-iot

ring-iot: main.cpp
	$(CC) -o ring-iot main.cpp jsoncpp.cpp $(CXXFLAGS) $(LIBS)

clean:
	rm -f *~ *.o ring-iot

