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
# Copyright (c) 2021 Jake Goerzen

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		plib
COMPONENT_VERSION=	1.8.5
COMPONENT_REVISION= 1
COMPONENT_PROJECT_URL=	http://plib.sourceforge.net
COMPONENT_SUMMARY=	PLIB - A Suite of Portable Game Libraries.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:485b22bf6fdc0da067e34ead5e26f002b76326f6371e2ae006415dea6a380a32
COMPONENT_ARCHIVE_URL=	http://plib.sourceforge.net/dist/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =	library/plib
COMPONENT_LICENSE=	LGPL
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION =	System/Libraries

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = cd $(COMPONENT_SRC) && autoreconf -if

CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
