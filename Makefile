CC = g++
CFLAGS := -Wall -std=c++11 \
		-I /home/houmin/ring-daemon/contrib/x86_64-linux-gnu/include/ \
		-lring -largon2 -lavcodec -lavdevice -lavfilter -lavformat -lavutil \
		-lboost_random -lboost_system -lcryptopp -lgmp -lgnutls -lgsm -lhogweed \
		-lnatpmp -lmsgpackc -lnettle -lopendht \
		-lpjlib-util-x86_64-pc-linux-gnu \
		-lpjmedia-audiodev-x86_64-pc-linux-gnu \
		-lpjmedia-codec-x86_64-pc-linux-gnu \
		-lpjmedia-videodev-x86_64-pc-linux-gnu \
		-lpjmedia-x86_64-pc-linux-gnu \
		-lpjnath-x86_64-pc-linux-gnu \
		-lpjsip-simple-x86_64-pc-linux-gnu \
		-lpjsip-ua-x86_64-pc-linux-gnu \
		-lpjsip-x86_64-pc-linux-gnu \
		-lpjsua2-x86_64-pc-linux-gnu \
		-lpjsua-x86_64-pc-linux-gnu \
		-lpj-x86_64-pc-linux-gnu \
		-lpostproc  -lrestbed \
		-lsrtp-x86_64-pc-linux-gnu \
	 	-lswresample  -lswscale -lx264 -lvpx -lyaml-cpp \
		-lpthread -ldl -lsndfile \
		-L/home/houmin/ring-daemon/contrib/x86_64-linux-gnu/lib -static 

all: ring-iot

ring-iot: main.cpp
	$(CC) -o ring-iot main.cpp $(CFLAGS)

clean:
	rm -f *~ *.o ring-iot

