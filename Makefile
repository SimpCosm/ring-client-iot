CC = g++
CXXFLAGS := -I/Users/weihoumin/ring-daemon-master/src/ \
            -L/Users/weihoumin/ring-daemon-master/src/.libs/ \
			-I/Users/weihoumin/ring-daemon-master/contrib/x86_64-apple-darwin15.6.0/include \
			-L/Users/weihoumin/ring-daemon-master/contrib/x86_64-apple-darwin15.6.0/lib \
            -Wall -std=c++11 
LIBS := -lring 

all: ring-iot

ring-iot: main.cpp
	$(CC) -o ring-iot main.cpp $(CXXFLAGS) $(LIBS)

clean:
	rm -f *~ *.o ring-iot

