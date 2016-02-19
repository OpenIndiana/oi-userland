all: build

build:
	cd DMZ-White/pngs && sh make.sh
	cd DMZ-Black/pngs && sh make.sh

install:
	mkdir -p $(DESTDIR)/usr/share/icons/DMZ-White/cursors
	mkdir -p $(DESTDIR)/usr/share/icons/DMZ-Black/cursors
	cp -r DMZ-White/xcursors/* $(DESTDIR)/usr/share/icons/DMZ-White/cursors
	cp -r DMZ-Black/xcursors/* $(DESTDIR)/usr/share/icons/DMZ-Black/cursors
