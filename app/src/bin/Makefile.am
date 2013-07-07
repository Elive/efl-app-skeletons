MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
   -DPACKAGE_BIN_DIR=\"$(bindir)\" \
   -DPACKAGE_LIB_DIR=\"$(libdir)\" \
   -DPACKAGE_DATA_DIR=\"$(pkgdatadir)\"

common_ldadd =  @ELEMENTARY_LIBS@ @EVIL_LIBS@
common_cflags =  @ELM_SKEL_CFLAGS@ @ELEMENTARY_CFLAGS@ @EVIL_CFLAGS@
common_ldflags =  @ELM_SKEL_LDFLAGS@

bin_PROGRAMS = elm_skel elm_skel_ql

elm_skel_SOURCES = \
   main.c

elm_skel_LDADD =  ${common_ldadd}
elm_skel_CFLAGS = ${common_cflags}
elm_skel_LDFLAGS = ${common_ldflags}

# QuickLaunch
elm_skel_ql_LTLIBRARIES = elm_skel_ql.la
elm_skel_ql_SOURCES = $(elm_skel_SOURCES)
elm_skel_ql_LDADD = ${common_ldadd}
elm_skel_ql_CFLAGS = ${common_cflags} -DELM_LIB_QUICKLAUNCH=1
elm_skel_ql_LDFLAGS = -module -avoid-version -no-undefined

elm_skel_qldir = $(libdir)
elm_skel_ql_la_SOURCES = $(elm_skel_SOURCES)
elm_skel_ql_la_LIBADD = ${common_ldadd}
elm_skel_ql_la_CFLAGS = ${common_cflags}
elm_skel_ql_la_LDFLAGS = -module -avoid-version -no-undefined
