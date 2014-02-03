MAINTAINERCLEANFILES = Makefile.in

.PHONY: doc
SUFFIXES: .lou .ps .pdf


if MY_APP_HAVE_DOC

.ps.pdf :
	ps2pdf $<

.lou.ps :
	lout -r3 -o $@ $<

doc-clean:
	-rm *.ps *.pdf *.li *.ld

doc: all

main.pdf:  main.lou

all: main.pdf

clean-local: doc-clean

else

doc:
	@echo "Documentation not built. Run ./configure --help"

endif

EXTRA_DIST = \
main.lou
