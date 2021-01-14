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
# Copyright (c) 2014 Alexander Pyhalov
#

BUILD_BITS=			64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		stardict
COMPONENT_VERSION=	3.0.6
COMPONENT_PROJECT_URL=	http://www.stardict.org/
COMPONENT_SUMMARY=	A powerful dictionary platform written in GTK+2
COMPONENT_FMRI=		system/desktop/stardict
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:6a0a695a8977604e0509a3db1bc6a67e53599b14f29494ba942f21d2c26b82e7
COMPONENT_ARCHIVE_URL=	ftp://tux.rainside.sk/gentoo/distfiles/$(COMPONENT_ARCHIVE)

TEST_TARGET:		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(MYSQL_BINDIR):$(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-deprecations
CONFIGURE_OPTIONS+=	--disable-festival
CONFIGURE_OPTIONS+=	--disable-advertisement
CONFIGURE_OPTIONS+=	--disable-gucharmap
CONFIGURE_OPTIONS+=	--disable-gnome-support

CPPFLAGS += -I$(MYSQL_INCDIR)
LDFLAGS += -L$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR)

LDFLAGS += -lnsl -lsocket

CONFIGURE_ENV += CPPFLAGS=$(CPPFLAGS)

REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils
REQUIRED_PACKAGES += $(MYSQL_BASEPKG)/library

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/speech/espeak
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
