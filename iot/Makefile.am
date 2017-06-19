include $(top_srcdir)/globals.mk

noinst_LTLIBRARIES = libclient_iot.la

BUILT_SOURCES=                      \
    iotcallmanager.adaptor.h       \
    iotconfigurationmanager.adaptor.h \
    iotinstance.adaptor.h

BUILT_SOURCES+=iotpresencemanager.adaptor.h
iotpresencemanager.adaptor.h: cx.ring.Ring.PresenceManager.xml Makefile.am
	iotxx-xml2cpp $< --adaptor=$@

if RING_VIDEO
BUILT_SOURCES+=iotvideomanager.adaptor.h
iotvideomanager.adaptor.h: cx.ring.Ring.VideoManager.xml Makefile.am
	iotxx-xml2cpp $< --adaptor=$@
endif

# Rule to generate the binding headers
iotcallmanager.adaptor.h: cx.ring.Ring.CallManager.xml Makefile.am
	iotxx-xml2cpp $< --adaptor=$@

# Rule to generate the binding headers
iotconfigurationmanager.adaptor.h: cx.ring.Ring.ConfigurationManager.xml Makefile.am
	iotxx-xml2cpp $< --adaptor=$@

# Rule to generate the binding headers
iotinstance.adaptor.h: cx.ring.Ring.Instance.xml Makefile.am
	iotxx-xml2cpp $< --adaptor=$@

libclient_iot_la_SOURCES = \
    iotcallmanager.cpp \
    iotcallmanager.h \
    iotconfigurationmanager.cpp  \
    iotconfigurationmanager.h \
    iotinstance.cpp  \
    iotclient.cpp \
    iotclient.h \
    iotinstance.h \
    iot_cpp.h \
    iotpresencemanager.cpp \
    iotpresencemanager.h \
    $(BUILT_SOURCES)

if RING_VIDEO
libclient_iot_la_SOURCES += iotvideomanager.cpp iotvideomanager.h
endif

libclient_iot_la_CXXFLAGS = -I../ \
            -I$(top_srcdir)/src \
            -I$(top_srcdir)/src/dring \
            -DPREFIX=\"$(prefix)\" \
            -DPROGSHAREDIR=\"${datadir}/ring\" \
            $(DBUSCPP_CFLAGS)

# Dbus service file
servicedir = $(datadir)/iot-1/services
service_DATA = cx.ring.Ring.service

# Dbus interface files
# https://iot.freedesktop.org/doc/iot-api-design.html#interface-files
interfacedir = $(datadir)/iot-1/interfaces
interface_DATA = cx.ring.Ring.CallManager.xml \
                 cx.ring.Ring.ConfigurationManager.xml \
                 cx.ring.Ring.Instance.xml \
                 cx.ring.Ring.PresenceManager.xml

if RING_VIDEO
interface_DATA += cx.ring.Ring.VideoManager.xml
endif

CLEANFILES= \
    $(BUILT_SOURCES) \
	cx.ring.Ring.service
