MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
   -I$(top_srcdir)/src/lib \
   -DPACKAGE_BIN_DIR=\"$(bindir)\" \
   -DPACKAGE_LIB_DIR=\"$(libdir)\" \
   -DPACKAGE_DATA_DIR=\"$(pkgdatadir)\" \
    @ELM_SKEL_CFLAGS@

bin_PROGRAMS = elm_skel elm_skel_ql

elm_skel_SOURCES = \
   main.c

elm_skel_LDADD =  $(top_builddir)/src/lib/libelm_skel.la
elm_skel_CFLAGS =
elm_skel_LDFLAGS =

# QuickLaunch
elm_skel_ql_LTLIBRARIES = elm_skel_ql.la
elm_skel_ql_SOURCES = $(elm_skel_SOURCES)
elm_skel_ql_LDADD = $(top_builddir)/src/lib/libelm_skel.la
elm_skel_ql_CFLAGS = -DELM_LIB_QUICKLAUNCH=1
elm_skel_ql_LDFLAGS =

elm_skel_qldir = $(libdir)
elm_skel_ql_la_SOURCES = $(elm_skel_SOURCES)
elm_skel_ql_la_LIBADD = @ELM_SKEL_LIBS@
elm_skel_ql_la_CFLAGS =
elm_skel_ql_la_LDFLAGS = -module @PROJECT_LTMODULE_FLAGS@
