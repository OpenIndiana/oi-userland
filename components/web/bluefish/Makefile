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

BUILD_BITS=			64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bluefish
COMPONENT_VERSION=	2.2.11
COMPONENT_PROJECT_URL=	http://bluefish.openoffice.nl/index.html
COMPONENT_SUMMARY=	Bluefish, a powerful editor for experienced web designers
COMPONENT_FMRI=		web/editor/bluefish
COMPONENT_CLASSIFICATION=	Development/Editors
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:454c877fc1dbddfcc65cc7ddaa3c5ceb17bc46e216baf7878f09dbf1dabdc2ff
COMPONENT_ARCHIVE_URL=	http://www.bennewitz.com/bluefish/stable/source/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv3

TEST_TARGET=		$(NO_TESTS)
include $(WS_TOP)/make-rules/common.mk

PATH=$(PATH.gnu)

CFLAGS += -DANSICPP

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	--disable-update-databases

CONFIGURE_ENV+=	PYTHON=$(PYTHON)


# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/character-map/gucharmap
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
