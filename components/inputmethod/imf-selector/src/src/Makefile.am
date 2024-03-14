SUBDIRS = icons

bin_SCRIPTS = imf-selector

imf-selector: imf-selector.py Makefile
	$(SED) -e 's|%%PYTHON%%|$(PYTHON)|g' $< >$@
	chmod +x $@

CLEANFILES = $(bin_SCRIPTS)

DISTCLEANFILES = $(CLEANFILES)

EXTRA_DIST = imf-selector.py
