phpwebdir = $(libdir)/$(PACKAGE)/plugin/phpweb

INCLUDES = \
	-Wall \
	-I$(top_srcdir) \
	-I../../src \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@
		
phpweb_LTLIBRARIES = libphpweb.la

libphpweb_la_SOURCES = \
	bima-phpweb.c bima-phpweb.h
	
libphpweb_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)

