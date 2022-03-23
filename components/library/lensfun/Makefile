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
# Copyright 2017 Aurelien Larcher
#
BUILD_BITS=	64_and_32
BUILD_STYLE=	cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         lensfun
COMPONENT_VERSION=      0.3.3
COMPONENT_SUMMARY=      Lensfun - library rectifying defects introduced by photographic equipment
COMPONENT_PROJECT_URL=  https://lensfun.github.io/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/lensfun/lensfun/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:57ba5a0377f24948972339e18be946af12eda22b7c707eb0ddd26586370f6765
COMPONENT_LICENSE=      GPLv3,LGPLv3
COMPONENT_FMRI=         image/library/lensfun
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE='Release'
CMAKE_OPTIONS+= -DBUILD_TESTS=ON
CMAKE_OPTIONS+= -DBUILD_LENSTOOL=ON
CMAKE_OPTIONS+= -DINSTALL_HELPER_SCRIPTS=OFF

COMPONENT_TEST_TRANSFORMS+= '-e "s/[0-9. ]*sec//g"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
