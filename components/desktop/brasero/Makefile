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
# Copyright (c) 2013 Ken Mays
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	brasero
COMPONENT_VERSION=	2.32.1
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	https://projects.gnome.org/brasero/
COMPONENT_SUMMARY=	Gnome CD/DVD burner
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:a0422cea30dbe470c06963f3c716a948442aed88f28701ea246752b5a73da5b9
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION = \
	(cd $(@D);  libtoolize --copy --force ; \
	aclocal -I . ; \
	autoheader ; \
	automake --add-missing --copy ; \
	autoconf)
                                        
CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--localstatedir=/var
CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--disable-scrollkeeper
CONFIGURE_OPTIONS+=	--enable-search
CONFIGURE_OPTIONS+=	--enable-playlist
CONFIGURE_OPTIONS+=	--enable-nautilus
CONFIGURE_OPTIONS+=	--enable-introspection
CONFIGURE_OPTIONS+=	--enable-libburnia
CONFIGURE_OPTIONS+=	--disable-gtk-doc
CONFIGURE_OPTIONS+=	--disable-inotify

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# common targets
build:	$(BUILD_32)

install:	$(INSTALL_32)

test:	$(NO_TESTS)

REQUIRED_PACKAGES += desktop/cd-burning/brasero
REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libunique
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += media/dvd+rw-tools
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
