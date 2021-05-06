AM_YFLAGS = -d -t -p qry -o qry_parser.c
AM_LFLAGS = -Pqry -oqry_scanner.c
INCLUDES = \
	-Wall \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_PLUGIN_DIR=\""$(libdir)/$(PACKAGE)/plugin"\" \
	-DPACKAGE_TEMPLATE_DIR=\""$(datadir)/$(PACKAGE)/template"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = bima

BUILT_SOURCE = qry_parser.h qry_parser.c  qry_scanner.c

bima_SOURCES = \
	main.c \
	callback.c callback.h \
	bima-app-data.c bima-app-data.h \
	bima-app-gui.c bima-app-gui.h \
	bima-module.c bima-module.h \
	bima-attribute.c bima-attribute.h \
	bima-connection.c bima-connection.h \
	bima-entity.c bima-entity.h \
	bima-foreign-key.c bima-foreign-key.h \
	bima-form.c bima-form.h \
	bima-property.c bima-property.h \
	bima-query.c bima-query.h \
	bima-query-field.c bima-query-field.h \
	bima-query-table.c bima-query-table.h \
	bima-relation.c bima-relation.h \
	bima-report.c bima-report.h \
	bima-template.c bima-template.h \
	bima-template-form.c bima-template-form.h \
	bima-utils.c bima-utils.h \
	bima-view.c bima-view.h \
	bima-plugin.c bima-plugin.h \
	dia-er-parse.c dia-er-parse.h \
	bma-file-parse.c bma-file-parse.h \
	file-utils.c file-utils.h \
	gen-db-script.c gen-db-script.h \
	gen-source.c gen-source.h \
	property.c property.h \
	qry_parser.y  \
	qry_scanner.l

bima_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

#qry_parser.h qry_parser.c: qry_parser.y
#	$(YACC) $(YFLAGS) $<

#qry_scanner.c: qry_scanner.l
