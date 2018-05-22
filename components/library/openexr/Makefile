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

#
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         openexr
COMPONENT_VERSION=      2.2.0
COMPONENT_FMRI=         library/openexr
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SUMMARY=      OpenEXR header files and libraries used to read and write OpenEXR images
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.openexr.com/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:36a012f6c43213f840ce29a8b182700f6cf6b214bea0d5735594136b44914231
COMPONENT_ARCHIVE_URL= \
  http://download.savannah.nongnu.org/releases/openexr/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D); libtoolize -f && aclocal -I m4 && autoconf -f -i)

# avoid unwind bug leading to core dump when C++ exceptions are thrown
COMPONENT_PRE_BUILD_ACTION = ($(GSED) -i -e 's;-lc -lgcc_s;-lc;' $(@D)/libtool)

PATCH_LEVEL = 0

# there seems to be no other way to enable large files support
CXXFLAGS += $(CPP_LARGEFILES)

# All C++ code should be built with -std=c++11 from now on.
CXXFLAGS += -std=c++11

# it seems that --with-pic doesn't get PIC flags to the C++ compiler
CXXFLAGS += $(CC_PIC)

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += LIBS="$(LIBS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-threading
CONFIGURE_OPTIONS += --enable-posix-sem
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --disable-dependency-tracking

COMPONENT_TEST_ENV += LANG=C

COMPONENT_TEST_TRANSFORMS += \
     '-e "s^-L$(CONFIGURE_LIBDIR.$(BITS))^^g"' \
     '-e "/libtool/d"' \
     '-e "/-m32/d"' \
     '-e "/-m64/d"' \
     '-e "/Nothing to be done/d"' \
     '-e "/Leaving directory/d"' \
     '-e "/Entering directory/d"' \
     '-e "/mv -f /d"' \
     '-e "/mkdir .libs/d"' \
     '-e "/is up to date/d"' \
     '-e "/creating IlmImfTest/d"' \
     '-e "/DEPDIR=/d"' \
     '-e "/\/var\/tmp/d"' \
     '-e "/\/usr\/gnu\/bin\/make/d"' \
     '-e "/^ld:/d"' \
     '-e "/Generating headers and data/d"'

build: $(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ilmbase
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
