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
BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         openexr
COMPONENT_VERSION=      2.2.0
COMPONENT_PROJECT_URL=  http://www.openexr.com/
COMPONENT_ARCHIVE_HASH= \
    sha256:36a012f6c43213f840ce29a8b182700f6cf6b214bea0d5735594136b44914231
COMPONENT_ARCHIVE_URL=  http://download.savannah.nongnu.org/releases/openexr/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/openexr
COMPONENT_ANITYA_ID=	13289

TPNO=			33075

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL = 0

# there seems to be no other way to enable large files support
CXXFLAGS += $(CPP_LARGEFILES)

# All C++ code should be built with -std=c++11 from now on.
CXXFLAGS += -std=c++11

# Needed to get the tests to work correctly. For more information see:
# https://github.com/openexr/openexr/issues/67
#CXXFLAGS += -ffloat-store

# it seems that --with-pic doesn't get PIC flags to the C++ compiler
CXXFLAGS += $(CC_PIC)

# START: remove this section (and the depend.mk file) when build servers are
# installed with the new ilmbase.
ILMBASE_PROTO =		$(WS_COMPONENTS)/ilmbase/build/prototype/$(MACH)
ILMBASE_LIBDIR.32 =	$(ILMBASE_PROTO)$(USRLIBDIR)
ILMBASE_LIBDIR.64 =	$(ILMBASE_PROTO)$(USRLIBDIR64)
ILMBASE_LIBDIR =	$(ILMBASE_LIBDIR.$(BITS))
CONFIGURE_ENV +=	LD_LIBRARY_PATH=$(ILMBASE_LIBDIR)
CONFIGURE_ENV +=	LDFLAGS="$(LDFLAGS) -L$(ILMBASE_LIBDIR)"
CONFIGURE_OPTIONS +=	--with-ilmbase-prefix=$(ILMBASE_PROTO)$(USRDIR)

# Remove ilmbase .la files to allow openexr libtool usage to work correctly.
COMPONENT_PRE_CONFIGURE_ACTION = \
	(cd $(ILMBASE_PROTO) ; \
        mlist=`/usr/bin/find . -name '*.la'` ; \
        for f in $$mlist ; do \
                $(RM) $$f ; \
        done)

# Needed to successfully run various binaries (such as b44ExpLogTable) during
# the build process.
COMPONENT_BUILD_ENV +=	LD_LIBRARY_PATH=$(ILMBASE_LIBDIR)

# Needed to successfully run the various test programs.
COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH=$(ILMBASE_LIBDIR)

# END: remove this section (and the depend.mk file) when build servers are
# installed with the new ilmbase.

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
     '-e "/Generating headers and data/d"'

CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --enable-threading
CONFIGURE_OPTIONS  +=           --enable-posix-sem
CONFIGURE_OPTIONS  +=           --with-pic

PROTOPKGCONFIGDIR.32 = $(PROTOPKGCONFIGDIR)
PROTOPKGCONFIGDIR.64 = $(PROTOPKGCONFIGDIR64)

# Delete /usr/lib/amd64 in libIlmImfUtil.la before install to prevent it
# using old library there when relinking.
COMPONENT_PRE_INSTALL_ACTION = \
	( cd $(BUILD_DIR_$(BITS))/IlmImfUtil ; \
	$(GSED) -i "s^-L$(CONFIGURE_LIBDIR.$(BITS))^^g" libIlmImfUtil.la )

COMPONENT_POST_INSTALL_ACTION = \
	( cd $(PROTOPKGCONFIGDIR.$(BITS)) ; \
	$(GSED) -i "s^-L$(CONFIGURE_LIBDIR.$(BITS))^^g" OpenEXR.pc )

REQUIRED_PACKAGES += library/ilmbase
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
