#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xscreensaver
COMPONENT_VERSION=	5.35
COMPONENT_PROJECT_URL=	http://www.jwz.org/xscreensaver/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1e6c8471a9af4862f38a6dd5c6e61fe12b052d35af44b2941904c6e333586b22
COMPONENT_ARCHIVE_URL=	http://ftp.lfs-matrix.net/pub/blfs/conglomeration/xscreensaver/$(COMPONENT_ARCHIVE)

PATCH_LEVEL=		0

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

COMPONENT_POST_UNPACK_ACTION=	( cp -r $(COMPONENT_DIR)/files/po-sun/* $(SOURCE_DIR)/po && \
					cp $(COMPONENT_DIR)/files/*.p5i.in $(SOURCE_DIR)/driver && \
					chmod a+x  $(SOURCE_DIR)/install-sh && \
					mkdir -p $(SOURCE_DIR)/mesa/GL && \
					ln -s /usr/include/mesa/*.h $(SOURCE_DIR)/mesa/GL )

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -if )

COMPONENT_PRE_CONFIGURE_ACTION += chmod -R u+r $(SOURCE_DIR)/ && \
			cp -r $(SOURCE_DIR)/* $(@D) && \
                        cd $(@D) && autoconf

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CONFIGURE_SCRIPT=	$(@D)/configure

CFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL  -std=gnu99 -D_FILE_OFFSET_BITS=64
CXXFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL -D_FILE_OFFSET_BITS=64
LDFLAGS+=	-I$(@D)/mesa/GL

CONFIGURE_ENV+=	"XGETTEXT=/usr/gnu/bin/xgettext"
CONFIGURE_ENV+= "GNOME_DATADIR=/usr/lib/xscreensaver/config"
CONFIGURE_ENV+= "GLADE_DATADIR=/usr/lib/xscreensaver/config"


CONFIGURE_OPTIONS+=	--enable-maintainer-mode
CONFIGURE_OPTIONS+=	--with-gnome
CONFIGURE_OPTIONS+=	--enable-gtk-doc
CONFIGURE_OPTIONS+=	--with-gtk2=/usr
CONFIGURE_OPTIONS+=	--with-pixbuf=/usr
CONFIGURE_OPTIONS+=	--enable-locking
CONFIGURE_OPTIONS+=	--with-pam=/usr
CONFIGURE_OPTIONS+=	--without-shadow
CONFIGURE_OPTIONS+=	--without-kerberos
CONFIGURE_OPTIONS+=	--with-dpms
CONFIGURE_OPTIONS+=	--with-xinput-ext
CONFIGURE_OPTIONS+=	--with-randr-ext
CONFIGURE_OPTIONS+=	--enable-root-passwd
CONFIGURE_OPTIONS+=	--with-gl=/usr
CONFIGURE_OPTIONS+=	--without-motif
CONFIGURE_OPTIONS+=	--with-jpeg=/usr
CONFIGURE_OPTIONS+=	--with-hackdir=/usr/lib/xscreensaver/hacks
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib/xscreensaver/bin
CONFIGURE_OPTIONS+=	--with-configdir=/usr/lib/xscreensaver/config/control-center-2.0
CONFIGURE_OPTIONS+=	--with-image-directory=/usr/share/pixmaps/backgrounds
CONFIGURE_OPTIONS+=	--with-text-file=/etc/motd
CONFIGURE_OPTIONS+=	--with-x-app-defaults=/usr/share/X11/app-defaults

COMPONENT_POST_CONFIGURE_ACTION+=	( \
	cd $(@D)/po && \
	make generate_potfiles_in -o Makefile && \
	make POTFILES -o Makefile && \
	make generate_potfiles_in POTFILES xscreensaver.pot -o Makefile &&  \
	touch stamp-it )

COMPONENT_INSTALL_ENV += MAKEFLAGS=-e install_prefix=$(PROTO_DIR)

../rss-glx/build/i86/.built:
	(cd ../rss-glx ; $(GMAKE) build)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) ../rss-glx/build/i86/.built
	perl ../rss-glx/build/i86/utils/rss-glx_install.pl $(PROTO_DIR)/usr/share/X11/app-defaults/XScreenSaver
test:		$(NO_TESTS)

REQUIRED_PACKAGES += gnome/accessibility/at-spi
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libglade
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libbonobo
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/orbit2
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxxf86misc
REQUIRED_PACKAGES += x11/library/libxxf86vm
REQUIRED_PACKAGES += x11/library/toolkit/libxt
