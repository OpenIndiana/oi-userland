#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libraw
COMPONENT_VERSION= 0.21.3
COMPONENT_SUMMARY= libraw - library for reading RAW files obtained from digital photo cameras
COMPONENT_PROJECT_URL= https://www.libraw.org/
COMPONENT_SRC_NAME= LibRaw
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/data/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:dba34b7fc1143503942fa32ad9db43e94f714e62a4a856e91617f8f3e1e0aa5c
COMPONENT_FMRI= image/library/libraw
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= CDDLv1.0,LGPLv2.1

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += ( cd $(@D); autoreconf -fiv )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-jpeg
CONFIGURE_OPTIONS += --enable-jasper
CONFIGURE_OPTIONS += --enable-lcms

# Manually added build dependencies
REQUIRED_PACKAGES += codec/jasper

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libjpeg-turbo
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
