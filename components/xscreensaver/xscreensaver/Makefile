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
# Don't change - compatibility issues
COMPONENT_VERSION=	5.11
HUMAN_VERSION= 		5.22
COMPONENT_PROJECT_URL=	http://www.jwz.org/xscreensaver/

COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:47b703ed22dce46a08f11ddd7d67d52e4f7ad8df844bdf956431069a0db36797
#COMPONENT_ARCHIVE_URL=	http://www.jwz.org/xscreensaver/$(COMPONENT_ARCHIVE)
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

COMPONENT_PRE_CONFIGURE_ACTION += chmod -R u+r $(SOURCE_DIR)/ && \
			cp -r $(SOURCE_DIR)/* $(@D) && \
                        cd $(@D) && autoconf

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CONFIGURE_SCRIPT=	$(@D)/configure

CFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL  -std=gnu99
CXXFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL
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

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../../make-rules/depend.mk


