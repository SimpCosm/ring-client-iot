include $(top_srcdir)/globals.mk

noinst_LTLIBRARIES = libclient_iot.la

libclient_iot_la_SOURCES = \
    iotclient.cpp \
    iotclient.h \
    iotconfigurationmanager.cpp \
    iotconfigurationmanager.h \
    iotpresencemanager.cpp \
    iotpresencemanager.h \
    iotcallmanager.cpp \
    iotcallmanager.h

if RING_VIDEO
libclient_iot_la_SOURCES += iotvideomanager.cpp iotvideomanager.h
endif

libclient_iot_la_CXXFLAGS = \
    -std=c++14 \
    -g \
    -Wall \
    -Wextra \
    -Wno-reorder \
    -Wno-unused-variable \
    -Wno-unused-parameter \
    -pedantic \
    -I$(top_srcdir)/src

libclient_iot_la_LDFLAGS = \
    -lpthread
