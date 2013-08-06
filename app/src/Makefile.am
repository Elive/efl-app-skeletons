AUTOMAKE_OPTIONS = subdir-objects

MAINTAINERCLEANFILES = Makefile.in
CLEANFILES =
BUILT_SOURCES =

DIST_SUBDIRS =
SUBDIRS =

lib_LTLIBRARIES =
bin_PROGRAMS =
bin_SCRIPTS =
noinst_PROGRAMS =
check_PROGRAMS =
TESTS =
EXTRA_DIST =

ELM_SKEL_INSTALL_DATA_HOOK=

AM_CPPFLAGS = -I. \
   -I$(top_srcdir) \
   -I$(top_srcdir)/src/lib \
   -DPACKAGE_BIN_DIR=\"$(bindir)\" \
   -DPACKAGE_LIB_DIR=\"$(libdir)\" \
   -DPACKAGE_DATA_DIR=\"$(datadir)/$(PACKAGE)\" \
   @ELM_SKEL_CFLAGS@

include Makefile_lib.am
include Makefile_bin.am
