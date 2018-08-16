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
#

PREFERRED_BITS= 64

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		atril
COMPONENT_MJR_VERSION=	1.18
COMPONENT_MNR_VERSION=	5
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	MATE PDF document viewer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9511f79f35df908792a588b888e8fb5aa843224fefe91875fc39cf984edf3e0a
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	desktop/pdf-viewer/atril
COMPONENT_CLASSIFICATION=	Applications/Office
COMPONENT_LICENSE= GPLv3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION=  cd $(@D)  && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))/mate
CONFIGURE_OPTIONS+=	--disable-static
# Atril's support for epub seems broken
CONFIGURE_OPTIONS+=	--disable-epub

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += library/desktop/mate/mate-common

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
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
