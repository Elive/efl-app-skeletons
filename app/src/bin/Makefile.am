MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
   -DPACKAGE_BIN_DIR=\"$(bindir)\" \
   -DPACKAGE_LIB_DIR=\"$(libdir)\" \
   -DPACKAGE_DATA_DIR=\"$(pkgdatadir)\"

common_ldadd =  @ELEMENTARY_LIBS@ @EVIL_LIBS@
common_cflags =  @ELM_SKEL_CFLAGS@ @ELEMENTARY_CFLAGS@ @EVIL_CFLAGS@
common_ldflags =  @ELM_SKEL_LDFLAGS@

bin_PROGRAMS = elm_skel

elm_skel_SOURCES = \
   main.c

elm_skel_LDADD =  ${common_ldadd}
elm_skel_CFLAGS = ${common_cflags}
elm_skel_LDFLAGS = ${common_ldflags}
