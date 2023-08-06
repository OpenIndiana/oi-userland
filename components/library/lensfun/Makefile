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

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         lensfun
COMPONENT_VERSION=      0.3.4
COMPONENT_SUMMARY=      Lensfun - library rectifying defects introduced by photographic equipment
COMPONENT_PROJECT_URL=  https://lensfun.github.io/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/lensfun/lensfun/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:dafb39c08ef24a0e2abd00d05d7341b1bf1f0c38bfcd5a4c69cf5f0ecb6db112
COMPONENT_FMRI=         image/library/lensfun
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=      GPLv3,LGPLv3

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PYVER=$(PYTHON_VERSION)

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE='Release'
CMAKE_OPTIONS+= -DBUILD_TESTS=ON
CMAKE_OPTIONS+= -DBUILD_LENSTOOL=ON
CMAKE_OPTIONS+= -DINSTALL_HELPER_SCRIPTS=OFF

COMPONENT_POST_INSTALL_ACTION += \
	if [ -d $(PROTO_DIR)/usr/lib/python3.9 ]; then \
		$(MKDIR) -p $(PROTO_DIR)/usr/lib/python3.9/vendor-packages ; \
		$(MV) $(PROTO_DIR)/usr/lib/python3.9/site-packages/* $(PROTO_DIR)/usr/lib/python3.9/vendor-packages ; \
		$(PYTHON) -m compileall $(PROTO_DIR)/usr/lib/python3.9/vendor-packages ; \
	fi ;

COMPONENT_TEST_TRANSFORMS+= '-e "s/[0-9. ]*sec//g"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
