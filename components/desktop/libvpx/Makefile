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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

# Prefer 32-bit over 64-bit for now.
BUILD_BITS=32_and_64
# For now, all things built for C++11 require gcc.
COMPILER= gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvpx
COMPONENT_VERSION=	1.4.0
COMPONENT_PROJECT_URL=	http://www.webmproject.org/
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:f582d9b2d60a592a4a3d8c32965ca2d2167e9ade38c6c30bac8801ff66a118e4
COMPONENT_ARCHIVE_URL=	http://downloads.webmproject.org/releases/webm/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libvpx
TPNO=			25516

# Requires newer version of system/linker from ON, available in S12 but not
# 11.3, so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif
 
# Required for 64-bit builds.
LDFLAGS += $(CC_BITS)
LDFLAGS += -Wl,-zgnu-version-script-compat

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Assumes GNU versions of tools such as awk and grep.
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_TEST_ENV += PATH=$(GNUBIN):$(PATH)

# Only deliver 64-bit binaries.
CONFIGURE_OPTIONS.32 += --disable-install-bins
CONFIGURE_OPTIONS += --disable-install-srcs
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-pic
CONFIGURE_OPTIONS += --enable-shared

# specify the targets
CONFIGURE_OPTIONS.sparc += --target=sparc-solaris-gcc
CONFIGURE_OPTIONS.i386.32 += --target=x86-solaris-gcc
CONFIGURE_OPTIONS.i386.64 += --target=x86_64-solaris-gcc

ifneq ($(MACH), sparc)
REQUIRED_PACKAGES += developer/yasm
endif
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
