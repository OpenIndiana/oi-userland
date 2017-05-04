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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           dcraw
COMPONENT_VERSION=        9.26.0
COMPONENT_REVISION=       2
COMPONENT_PROJECT_URL=    https://www.cybercom.net/~dcoffin/dcraw/
COMPONENT_SUMMARY=        dcraw - Decoding RAW digital photos
COMPONENT_SRC=            $(COMPONENT_NAME)
COMPONENT_ARCHIVE=        $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=        \
    sha256:85791d529e037ad5ca09770900ae975e2e4cc1587ca1da4192ca072cbbfafba3
COMPONENT_ARCHIVE_URL=        http://cybercom.net/~dcoffin/dcraw/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	dcraw.license
COMPONENT_FMRI=		image/dcraw
COMPONENT_CLASSIFICATION=	System/Media

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION=( cd $(@D) && rm -f install )

# build with the distribution preferred libjpeg implementation
CFLAGS               += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS             += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS              += $(JPEG_LDFLAGS)

COMPONENT_BUILD_ARGS += CC=$(CC)
COMPONENT_BUILD_ARGS += CXX=$(CXX)
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"

                                        
# common targets
build:                $(BUILD_32)

install:        $(INSTALL_32)

test:                $(NO_TESTS)

REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += image/library/$(JPEG_IMPLEM)
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
