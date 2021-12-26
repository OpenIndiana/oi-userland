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
# Copyright 2015 Aurelien Larcher
# Copyright 2021 David Stes
#

BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libjpeg9-ijg
COMPONENT_VERSION=	9.4.0
LIBJPEG_API_VERSION= 9d
COMPONENT_FMRI= 	image/library/libjpeg9-ijg
COMPONENT_PROJECT_URL=	http://www.ijg.org/
COMPONENT_SUMMARY=	libjpeg - Independent JPEG Group library version 9d
COMPONENT_SRC=		jpeg-$(LIBJPEG_API_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
 sha256:6c434a3be59f8f62425b2e3c077e785c9ce30ee5874ea1c270e843f273ba71ee
COMPONENT_ARCHIVE_URL=	http://www.ijg.org/files/jpegsrc.v$(LIBJPEG_API_VERSION).tar.gz
COMPONENT_LICENSE=	IJG,GPLv2.0
COMPONENT_CLASSIFICATION=System/Multimedia Libraries

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_DEFAULT_DIRS=no

CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS+= --includedir=$(CONFIGURE_INCLUDEDIR)/$(COMPONENT_NAME)
CONFIGURE_OPTIONS.32+= --bindir=$(USRLIBDIR)/$(COMPONENT_NAME)/bin
CONFIGURE_OPTIONS.32+= --libdir=$(USRLIBDIR)/$(COMPONENT_NAME)/lib
CONFIGURE_OPTIONS.64+= --bindir=$(USRLIBDIR)/$(COMPONENT_NAME)/bin/$(MACH64)
CONFIGURE_OPTIONS.64+= --libdir=$(USRLIBDIR)/$(COMPONENT_NAME)/lib/$(MACH64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
