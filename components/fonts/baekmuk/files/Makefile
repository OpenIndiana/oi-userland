all: build

build:

install:
	mkdir -p $(DESTDIR)/usr/share/fonts/TrueType/baekmuk
	cp ttf/*.ttf $(DESTDIR)/usr/share/fonts/TrueType/baekmuk
	cd $(DESTDIR)/usr/share/fonts/TrueType/baekmuk \
		&& /usr/bin/mkfontscale \
		&& /usr/bin/mkfontdir
