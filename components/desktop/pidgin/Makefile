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
# Copyright 2017 Gary Mills
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pidgin
COMPONENT_VERSION=	2.12.0
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://www.pidgin.im
COMPONENT_SUMMARY=	Multiprotocol Instant Messaging Client
COMPONENT_FMRI=		communication/im/pidgin
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8c3d3536d6d3c971bd433ff9946678af70a0f6aa4e6969cc2a83bb357015b7f8
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/Pidgin/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	pidgin.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

# We use libncurses and libpanel from /usr/gnu/lib
LDFLAGS += -L/usr/gnu/lib -R/usr/gnu/lib

CPPFLAGS += -D_FILE_OFFSET_BITS=64

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
			                libtoolize --force && \
					intltoolize --force --copy --automake && \
					aclocal -I. && \
					automake -a -f -c &&\
					autoconf )

COMPONENT_PRE_CONFIGURE_ACTION = ( cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -rp $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE))

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-gnutls=no
CONFIGURE_OPTIONS+=	--with-nss-includes=/usr/include/mps
CONFIGURE_OPTIONS+=	--with-nss-libs=/usr/lib/mps
CONFIGURE_OPTIONS+=	--with-nspr-includes=/usr/include/mps
CONFIGURE_OPTIONS+=	--with-nspr-libs=/usr/lib/mps
CONFIGURE_OPTIONS+=	--enable-gnome-keyring
CONFIGURE_OPTIONS+=	--disable-gevolution
CONFIGURE_OPTIONS+=	--enable-cap
CONFIGURE_OPTIONS+=	--disable-meanwhile
CONFIGURE_OPTIONS+=	--disable-nm
CONFIGURE_OPTIONS+=	--enable-consoleui
CONFIGURE_OPTIONS+=	--with-ncurses-headers=/usr/include/ncurses
CONFIGURE_OPTIONS+=	--disable-vv
CONFIGURE_OPTIONS+=	--enable-perl=yes

CONFIGURE_ENV+=	INTLTOOL_PERL=$(PERL)
CONFIGURE_ENV+=	PERL=$(PERL)
CONFIGURE_ENV+=	perlpath=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

CONFIGURE_ENV+=	CPPFLAGS="$(CPPFLAGS)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtkspell
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxscrnsaver
