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
COMPONENT_VERSION= 0.18.11
COMPONENT_SUMMARY= libraw - library for reading RAW files obtained from digital photo cameras
COMPONENT_PROJECT_URL= http://www.libraw.org/
COMPONENT_FMRI= image/library/libraw
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_SRC_NAME= LibRaw
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= http://www.libraw.org/data/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:7cf724a40a0d8915869498f51062a952167e4f5bae2b6920542c9e0e079a471d
COMPONENT_LICENSE= CDDLv1.0,LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Use default libjpeg
CXXFLAGS+= $(JPEG_CPPFLAGS)
CXXFLAGS+= $(JPEG_CXXFLAGS)
CONFIGURE_ENV+= LDFLAGS="$(JPEG_LDFLAGS)"
CONFIGURE_ENV+= LIBS="$(JPEG_LDFLAGS)"

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-jpeg
CONFIGURE_OPTIONS+= --enable-jasper
CONFIGURE_OPTIONS+= --enable-lcms
CONFIGURE_OPTIONS+= --disable-demosaic-pack-gpl2
CONFIGURE_OPTIONS+= --disable-demosaic-pack-gpl3

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
