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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         openexr
COMPONENT_VERSION=      1.6.1
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.openexr.com/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:c616906ab958de9c37bb86ca7547cfedbdfbad5e1ca2a4ab98983c9afa6a5950
COMPONENT_ARCHIVE_URL=  http://download.savannah.nongnu.org/releases/openexr/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0

# there seems to be no other way to enable large files support
CXXFLAGS += $(CPP_LARGEFILES)
# it seems that --with-pic doesn't get PIC flags to the C++ compiler
CXXFLAGS += $(CC_PIC)
# libtools seems to be forcing -nolibs, so we have to add back libc, libm,
# libCstd and libCrun. The last two are needed because with Studio 12.2
# (and beyond), there is a bug in the CC driver that is not correctly using
# the '-library=Cstd,Crun' we are passing to it.
LIBS += -lc -lm -lCstd -lCrun

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += LIBS="$(LIBS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --enable-threading
CONFIGURE_OPTIONS  +=           --enable-posix-sem
CONFIGURE_OPTIONS  +=           --with-pic

build: $(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk
