SUBDIRS=bin conf grooid lib
GROOVY_MAJOR_VERSION ?= 4.0
all: build

build: 

install: 
	mkdir -p $(DESTDIR)/usr/share/groovy-$(GROOVY_MAJOR_VERSION)
	mkdir -p $(DESTDIR)/usr/bin
	cp -rf $(SUBDIRS) $(DESTDIR)/usr/share/groovy-$(GROOVY_MAJOR_VERSION)
	ln -frs $(DESTDIR)/usr/share/groovy-$(GROOVY_MAJOR_VERSION)/bin/* $(DESTDIR)/usr/bin
