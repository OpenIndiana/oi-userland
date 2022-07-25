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
# Copyright 2018-2019 Michal Nowak
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         xscreensaver
COMPONENT_VERSION=      5.44
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://www.jwz.org/xscreensaver/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:73d8089cfc7d7363b5dac99b5b01dffb3429d0a855e6af16ce9a4b7777017b95
COMPONENT_ARCHIVE_URL=  https://www.jwz.org/xscreensaver/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         desktop/xscreensaver

PATCH_LEVEL=		0

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION=	( cp $(COMPONENT_DIR)/files/*.p5i.in $(SOURCE_DIR)/driver && \
					chmod a+x  $(SOURCE_DIR)/install-sh && \
					mkdir -p $(SOURCE_DIR)/mesa/GL && \
					ln -s /usr/include/mesa/*.h $(SOURCE_DIR)/mesa/GL )

# po/Makefile.in.in is modified by hand and broken by autoreconf
COMPONENT_PREP_ACTION = ( $(CP) $(@D)/po/Makefile.in.in $(@D)/po/Makefile.in.in.jwz ; \
			  cd $(@D) && autoreconf -if ; \
                          $(CP) $(@D)/po/Makefile.in.in.jwz $(@D)/po/Makefile.in.in )

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION += chmod -R u+r $(SOURCE_DIR)/ && \
					cp -rpP $(SOURCE_DIR)/* $(@D)

CONFIGURE_SCRIPT=	$(@D)/configure

CFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL  -std=c99 -D_FILE_OFFSET_BITS=64
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

COMPONENT_BUILD_TARGETS=all

../rss-glx/build/i86/.built:
	(cd ../rss-glx && $(GMAKE) build)
	 
COMPONENT_INSTALL_ENV += MAKEFLAGS=-e install_prefix=$(PROTO_DIR)
	 
install: $(INSTALL_64) ../rss-glx/build/i86/.built
	$(PERL) ../rss-glx/build/$(MACH64)/utils/rss-glx_install.pl $(PROTO_DIR)/usr/share/X11/app-defaults/XScreenSaver

# Build dependencies
REQUIRED_PACKAGES += image/library/$(JPEG_IMPLEM)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += x11/library/mesa
# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
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
REQUIRED_PACKAGES += x11/library/toolkit/libxt
