lib_LTLIBRARIES=goom.la

AM_CXXFLAGS=-I$(top_srcdir)/lib/goom2k4-0/src

goom_la_SOURCES=Main.cpp 
goom_la_LIBADD=$(top_srcdir)/lib/goom2k4-0/src/.libs/libgoom2.a
goom_la_LDFLAGS=-module -avoid-version
goom_la_DEPENDENCIES=goom

goom:
	make -C $(top_srcdir)/lib/goom2k4-0
