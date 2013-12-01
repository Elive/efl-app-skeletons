ACLOCAL_AMFLAGS = -I m4
AM_MAKEFLAGS = --no-print-directory
AM_DISTCHECK_CONFIGURE_FLAGS = \
   --with-tests=regular

SUBDIRS = src data

MAINTAINERCLEANFILES = \
   Makefile.in \
   $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz \
   $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.bz2 \
   aclocal.m4 \
   config.guess \
   config.cache-env \
   config.h.in \
   config.sub \
   configure \
   compile \
   depcomp \
   install-sh \
   ltconfig \
   ltmain.sh \
   missing \
   mkinstalldirs \
   stamp-h.in \
   stamp-h \
   m4/libtool.m4 \
   m4/lt~obsolete.m4 \
   m4/ltoptions.m4 \
   m4/ltsugar.m4 \
   m4/ltversion.m4

EXTRA_DIST = \
   README \
   AUTHORS \
   COPYING \
   autogen.sh \
   elm_skel.pc.in \
   m4/efl_attribute.m4 \
   m4/efl_compiler.m4 \
   m4/efl_path_max.m4 \
   m4/efl_binary.m4 \
   m4/project_init.m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = elm_skel.pc


# Unit tests

if ELM_SKEL_ENABLE_COVERAGE

lcov-reset:
	@rm -rf $(top_builddir)/coverage
	@find $(top_builddir) -name "*.gcda" -delete
	@lcov --zerocounters --directory $(top_builddir)

lcov-report:
	@mkdir $(top_builddir)/coverage
	lcov --capture --compat-libtool --output-file $(top_builddir)/coverage/coverage.info --directory $(top_builddir) --base-directory $(top_srcdir)/src/
	lcov --remove $(top_builddir)/coverage/coverage.info '*.h' --output-file $(top_builddir)/coverage/coverage.cleaned.info
	lcov --remove $(top_builddir)/coverage/coverage.cleaned.info '*/tests/*' --output-file $(top_builddir)/coverage/coverage.cleaned2.info
	genhtml --branch-coverage -t "$(PACKAGE_STRING)" -o $(top_builddir)/coverage/html $(top_builddir)/coverage/coverage.cleaned2.info
	@echo "Coverage Report at $(top_builddir)/coverage/html"

endif

if ELM_SKEL_ENABLE_TESTS

lcov-check:
if ELM_SKEL_ENABLE_COVERAGE
	@$(MAKE) $(AM_MAKEFLAGS) lcov-reset
endif
	@$(MAKE) $(AM_MAKEFLAGS) check
if ELM_SKEL_ENABLE_COVERAGE
	@$(MAKE) $(AM_MAKEFLAGS) lcov-report
endif

endif
