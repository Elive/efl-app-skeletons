MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = default/default.edc

EDJE_CC = @edje_cc@
AM_V_EDJ = $(am__v_EDJ_@AM_V@)
am__v_EDJ_ = $(am__v_EDJ_@AM_DEFAULT_V@)
am__v_EDJ_0 = @echo "  EDJ   " $@;
EDJE_CC_FLAGS = \
	    -id $(top_srcdir)/data/images

filesdir = $(datadir)/$(PACKAGE)/themes
files_DATA = $(top_builddir)/data/themes/default.edj

$(top_builddir)/data/themes/default.edj: $(top_srcdir)/data/themes/default/default.edc
	$(AM_V_EDJ)$(EDJE_CC) $(EDJE_CC_FLAGS) $< $@

clean-local:
	rm -f  *.edj
	rm -rf autom4te.cache

