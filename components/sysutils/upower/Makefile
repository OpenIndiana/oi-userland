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
# Copyright 2017 Alexander Pyhalov
# Copyright 2020 Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		upower
COMPONENT_VERSION=	0.99.11
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://upower.freedesktop.org/
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=		system/upower
COMPONENT_SUMMARY=	A service for enumerating and querying data related to power devices
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:64b5ffbfccd5bdb15d925777979a4dbee1a957f9eaeb158dc76175267eddbdef
COMPONENT_ARCHIVE_URL= \
	http://upower.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CPPFLAGS += $(CPP_LARGEFILES)

COMPONENT_PREP_ACTION = (cd $(@D) && \
				libtoolize --copy --force &&\
				aclocal -I . &&\
				autoheader &&\
				automake -c -f -a &&\
				autoconf )

CONFIGURE_BINDIR.64 = /usr/bin

CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk-doc
CONFIGURE_OPTIONS += --enable-man-pages
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
