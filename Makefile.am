ringlibdir = $(libdir)/ring

SUBDIRS=iot

ringlib_PROGRAMS = ringcli
ringcli_SOURCES = main.cpp
ringcli_CXXFLAGS = -I$(top_srcdir)/src \
                   -I$(top_srcdir)/src/dring \
                   -DTOP_BUILDDIR=\"$$(cd "$(top_builddir)"; pwd)\"
ringcli_LDADD = iot/libclient_iot.la $(top_builddir)/src/libring.la

