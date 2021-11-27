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
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2020 Marco van Wieringen
# Copyright (c) 2021 Tim Mooney.  All rights reserved
#

BUILD_BITS=		64

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		atril
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	0
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	https://www.mate-desktop.org
COMPONENT_SUMMARY=	MATE PDF document viewer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:715e766eaede3fa5d8ca300fa3319fb2b63055dfdc6e971d8750c2aec624e45f
COMPONENT_ARCHIVE_URL=	https://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/pdf-viewer/atril
COMPONENT_CLASSIFICATION=	Applications/Office
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

COMPONENT_PREP_ACTION=  cd $(@D) && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))/mate
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--enable-introspection
# tested atril 1.26.0 with epub support and it's still poor.  It
# uses webkitgtk2 for the epubs and can open some, but fails on
# others.  Worse, Atril spawns webkitgtk2 processes for non-epub
# documents too.  Leave epub disabled until that improves, maybe
# with an updated webkitgtk?
CONFIGURE_OPTIONS+=	--disable-epub

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

# test suite requires a python module called 'dogtail'
# for testing GUI applications which we don't currently package.

# Build dependencies
REQUIRED_PACKAGES += library/desktop/mate/mate-common

# formerly part of auto-generated, no longer included
#REQUIRED_PACKAGES += desktop/mate/caja/caja-extensions
#REQUIRED_PACKAGES += x11/library/libx11

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/mate/caja
REQUIRED_PACKAGES += image/djvulibre
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libspectre
REQUIRED_PACKAGES += library/libsynctex
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
