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

COMPONENT_NAME=         ilmbase
COMPONENT_VERSION=      2.2.0
COMPONENT_FMRI=         library/ilmbase
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SUMMARY=      Ilmbase libraries used to read and write OpenEXR images
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.openexr.com/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:ecf815b60695555c1fbc73679e84c7c9902f4e8faa6e8000d2f905b8b86cedc7
COMPONENT_ARCHIVE_URL= \
  http://download.savannah.nongnu.org/releases/openexr/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL = 0

# ltmain.sh is buggy and cause issues with C++ exceptions:
# https://debbugs.gnu.org/cgi/bugreport.cgi?bug=16452
COMPONENT_PREP_ACTION = (cd $(@D); libtoolize -f && aclocal -I m4 && autoconf -f -i)

# avoid unwind bug leading to core dump when C++ exceptions are thrown
+COMPONENT_PRE_BUILD_ACTION = ($(GSED) -i -e 's;-lc -lgcc_s;-lc;' $(@D)/libtool)

# All C++ code should be built with -std=c++11 from now on.
CXXFLAGS += -std=c++11

# To allow the 32-bit version of IexMath/IexMathFpu.cpp to compile as there is
# only a 64-bit definition of the typedef struct fpu { ... } fpregset_t;
# definition in /usr/include/sys/regset.h
CXXFLAGS += -U__i386__

# Needed to get the tests to work correctly. For more information see:
# https://github.com/openexr/openexr/issues/67
CXXFLAGS += -ffloat-store

# there seems to be no other way to enable large files support
CXXFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-threading
CONFIGURE_OPTIONS += --enable-posix-sem
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --enable-large-stack
CONFIGURE_OPTIONS += --disable-dependency-tracking

COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master
# Strip compilation lines from test output
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*$(CXX).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^config.status: .*$$|XXX_CC_XXX|g" ' \
	'-e "s|^mv -f .*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*matrices took .* clocks.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*speed up.*$$|XXX_CC_XXX|g" ' \
	'-e "/is up to date/d"' \
	'-e "/Nothing to be done/d"' \
	'-e "/Leaving directory/d"' \
	'-e "/Entering directory/d"' \
	'-e "/^XXX_CC_XXX$$/d" '

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test:	 $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
