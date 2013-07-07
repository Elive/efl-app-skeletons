MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = -I. \
   -I$(top_srcdir) \
   -I$(top_srcdir)/src/lib \
   -DPACKAGE_BIN_DIR=\"$(bindir)\" \
   -DPACKAGE_LIB_DIR=\"$(libdir)\" \
   -DPACKAGE_DATA_DIR=\"$(datadir)/$(PACKAGE)\" \
   @ELEMENTARY_CFLAGS@ \
   @EVIL_CFLAGS@

includes_HEADERS = elm_skel.h
includesdir = $(includedir)/elm_skel-@VMAJ@

lib_LTLIBRARIES = libelm_skel.la

libelm_skel_la_SOURCES = \
   elm_skel.c

libelm_skel_la_LIBADD = @ELEMENTARY_LIBS@ @EVIL_LIBS@
libelm_skel_la_CFLAGS =
libelm_skel_la_LDFLAGS = -no-undefined @lt_enable_auto_import@ -version-info @version_info@ @release_info@

