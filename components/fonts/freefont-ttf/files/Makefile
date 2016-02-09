all: build

build:

install:
	mkdir -p $(DESTDIR)/usr/share/fonts/TrueType/freefont
	cp *.ttf $(DESTDIR)/usr/share/fonts/TrueType/freefont
	cd $(DESTDIR)/usr/share/fonts/TrueType/freefont \
		&& /usr/bin/mkfontscale \
		&& /usr/bin/mkfontdir
