BINDIR ?= /usr/bin
DESTDIR ?= ..overridden in spec file..

all:

install: install-xsl install-img install-extensions install-misc

install-xsl:
	mkdir -p $(DESTDIR)/common
	mkdir -p $(DESTDIR)/fo
	mkdir -p $(DESTDIR)/html
	mkdir -p $(DESTDIR)/htmlhelp/doc
	mkdir -p $(DESTDIR)/javahelp
	mkdir -p $(DESTDIR)/lib
	mkdir -p $(DESTDIR)/template
	mkdir -p $(DESTDIR)/xhtml
	mkdir -p $(DESTDIR)/manpages
	mkdir -p $(DESTDIR)/profiling
	cp common/*.dtd $(DESTDIR)/common
	cp common/*.xml $(DESTDIR)/common
	cp common/*.xsl $(DESTDIR)/common
	cp fo/*.xml $(DESTDIR)/fo
	cp fo/*.xsl $(DESTDIR)/fo
	cp html/*.xml $(DESTDIR)/html
	cp html/*.xsl $(DESTDIR)/html
	cp htmlhelp/*.xsl $(DESTDIR)/htmlhelp
	cp javahelp/*.xsl $(DESTDIR)/javahelp
	cp lib/lib.xsl $(DESTDIR)/lib
	cp template/*.xml $(DESTDIR)/template
	cp template/*.xsl $(DESTDIR)/template
	cp xhtml/*.xsl $(DESTDIR)/xhtml
	cp manpages/*.xsl $(DESTDIR)/manpages
	cp profiling/*.xsl $(DESTDIR)/profiling

install-img:
	mkdir -p $(DESTDIR)/images/callouts
	cp images/*.gif $(DESTDIR)/images
	cp images/*.png $(DESTDIR)/images
	cp images/callouts/*.png $(DESTDIR)/images/callouts

install-extensions:
	mkdir -p $(DESTDIR)/extensions
	cp -r extensions/* $(DESTDIR)/extensions

install-misc:
	cp VERSION $(DESTDIR)
