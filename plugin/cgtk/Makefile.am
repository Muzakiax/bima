cgtkdir = $(libdir)/$(PACKAGE)/plugin/cgtk

INCLUDES = \
	-Wall \
	-I$(top_srcdir) \
	-I../../src \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@
		
cgtk_LTLIBRARIES = libcgtk.la

libcgtk_la_SOURCES = \
	bima-cgtk-utils.c bima-cgtk-utils.h \
	bima-cgtk-frm-input.c bima-cgtk-frm-input.h \
	bima-cgtk.c bima-cgtk.h
	
libcgtk_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)

#sample_plugin: bma-cgtk.c bma-cgtk.h  ../../src/bma-plugin.h ../../src/bma-app-gui.h
#	gcc -fPIC -c bma-cgtk.c -I../../src -o bma-sample-plugin.o `pkg-config --cflags gtk+-2.0 gmodule-2.0` `xml2-config --cflags`
#	gcc -shared -o bma-sample-plugin.so bma-sample-plugin.o 
