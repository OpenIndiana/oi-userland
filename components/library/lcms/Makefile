#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =        lcms
COMPONENT_VERSION=      1.19
COMPONENT_REVISION=		3
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.littlecms.com/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:80ae32cb9f568af4dc7ee4d3c05a4c31fc513fc3e31730fed0ce7378237273a9
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/lcms/files/lcms/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/lcms

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && libtoolize -f && autoreconf -fi)

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# It seems that we have no other way to designate that we want large file support
CFLAGS += $(CPP_LARGEFILES)
CXXFLAGS += $(CPP_LARGEFILES)

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYTHONMODULEDIR="$(PYTHON_VENDOR_PACKAGES)"

CONFIGURE_OPTIONS  +=           --includedir=/usr/include/lcms
CONFIGURE_OPTIONS  +=           --enable-shared
CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --with-jpeg
CONFIGURE_OPTIONS  +=           --with-tiff
CONFIGURE_OPTIONS  +=           --with-zlib
CONFIGURE_OPTIONS  +=           --with-python
CONFIGURE_OPTIONS  +=           --with-pic

CONFIGURE_OPTIONS += --disable-rpath
CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

PKG_PROTO_DIRS +=	$(COMPONENT_SRC)

# in order to run the tests, we need to use cloney
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_POST_CONFIGURE_ACTION = \
    ( cd $(@D); \
    $(CP) -p $(SOURCE_DIR)/include/lcms.h ./include/ ; \
    $(RM) -f $(SOURCE_DIR)/include/icc34.h ; \
    $(CP) -p include/icc34.h $(SOURCE_DIR)/include/ )

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
	$(PYTHON.2.7.32) -m compileall $(PROTO_DIR)/usr/lib/python2.7/vendor-packages


test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/lcms
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
