MAINTAINERCLEANFILES = Makefile.in

EDJE_CC = @edje_cc@
AM_V_EDJ = $(am__v_EDJ_@AM_V@)
am__v_EDJ_ = $(am__v_EDJ_@AM_DEFAULT_V@)
am__v_EDJ_0 = @echo "  EDJ   " $@;

EDJE_CC_FLAGS = \
	    -id $(top_srcdir)/data/themes/default/images

filesdir = $(datadir)/$(PACKAGE)/themes
files_DATA = default.edj

default.edj: default.edc
	$(AM_V_EDJ)$(EDJE_CC) $(EDJE_CC_FLAGS) $< $@

clean-local:
	rm -f  *.edj

EXTRA_DIST = \
   default.edc \
   images/frame.png \
   images/tunnel.png \
   images/left_door.png \
   images/right_door.png
