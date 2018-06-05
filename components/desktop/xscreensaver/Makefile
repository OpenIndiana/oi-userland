#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Gary Mills
# Copyright 2017 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xscreensaver
COMPONENT_VERSION=	5.39
COMPONENT_PROJECT_URL=	https://www.jwz.org/xscreensaver/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:48ce1880f18b5321182be0c033aeceb5ec5628a1505b9d1ff69dbf06093c2426
COMPONENT_ARCHIVE_URL=	http://ftp.lfs-matrix.net/pub/blfs/conglomeration/xscreensaver/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/xscreensaver

PATCH_LEVEL=		0

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION=	( cp $(COMPONENT_DIR)/files/*.p5i.in $(SOURCE_DIR)/driver && \
					chmod a+x  $(SOURCE_DIR)/install-sh && \
					mkdir -p $(SOURCE_DIR)/mesa/GL && \
					ln -s /usr/include/mesa/*.h $(SOURCE_DIR)/mesa/GL )

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -if )

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION += chmod -R u+r $(SOURCE_DIR)/ && \
					cp -rpP $(SOURCE_DIR)/* $(@D)


CONFIGURE_SCRIPT=	$(@D)/configure

CFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL  -std=gnu99 -D_FILE_OFFSET_BITS=64
CXXFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL -D_FILE_OFFSET_BITS=64
LDFLAGS+=	-I$(@D)/mesa/GL 

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_ENV+=	"XGETTEXT=/usr/gnu/bin/xgettext"

CONFIGURE_OPTIONS+=	--with-pixbuf=/usr 
CONFIGURE_OPTIONS+=	--enable-locking
CONFIGURE_OPTIONS+=	--with-pam=/usr 
CONFIGURE_OPTIONS+=	--without-shadow
CONFIGURE_OPTIONS+=	--without-kerberos 
CONFIGURE_OPTIONS+=	--with-xinput-ext
CONFIGURE_OPTIONS+=	--with-randr-ext
CONFIGURE_OPTIONS+=	--enable-root-passwd
CONFIGURE_OPTIONS+=	--with-gl=/usr
CONFIGURE_OPTIONS+=	--without-motif
CONFIGURE_OPTIONS+=	--with-hackdir=/usr/lib/xscreensaver/hacks 
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib/xscreensaver/bin
CONFIGURE_OPTIONS+=	--with-configdir=/usr/lib/xscreensaver/config/control-center-2.0
CONFIGURE_OPTIONS+=	--with-image-directory=/usr/share/pixmaps/backgrounds
CONFIGURE_OPTIONS+=	--with-text-file=/etc/motd
CONFIGURE_OPTIONS+=	--with-x-app-defaults=/usr/share/X11/app-defaults
CONFIGURE_OPTIONS+=	--with-jpeg
CONFIGURE_OPTIONS+=	--with-png
CONFIGURE_OPTIONS+=	--with-gl

COMPONENT_INSTALL_ENV += MAKEFLAGS=-e install_prefix=$(PROTO_DIR)

../rss-glx/build/i86/.built:
	(cd ../rss-glx ; $(GMAKE) build)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64) ../rss-glx/build/i86/.built
	perl ../rss-glx/build/i86/utils/rss-glx_install.pl $(PROTO_DIR)/usr/share/X11/app-defaults/XScreenSaver
test:		$(NO_TESTS)

REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += image/library/$(JPEG_IMPLEM)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxkbfile
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxxf86misc
REQUIRED_PACKAGES += x11/library/libxxf86vm
REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += x11/library/toolkit/libxt
