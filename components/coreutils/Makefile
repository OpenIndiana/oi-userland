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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		coreutils
COMPONENT_VERSION=	8.23
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/coreutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ec43ca5bcfc62242accb46b7f121f6b684ee21ecd7d075059bf650ff9e37b82d
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/coreutils/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-coreutils

TPNO=			18521

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# We need the GNU grep command to configure/build.
PATH=/usr/gnu/bin:/usr/bin

PATCH_LEVEL=		0

CONFIGURE_PREFIX	 =	/usr/gnu
CONFIGURE_OPTIONS	+=	--bindir=/usr/gnu/bin
CONFIGURE_OPTIONS	+=	--libdir=/usr/lib
CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS	+=	CPPFLAGS=-I/usr/include/gmp
CONFIGURE_OPTIONS	+=	CFLAGS="$(CFLAGS)"

# Recreate configure and Makefile to pick up changes in .../src/local.mk
COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f && automake)

# Needed to get tests to work when run directly from the tests subdirectory.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=		V=1

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Get the binaries to test from the component proto area.
COMPONENT_TEST_ENV +=   PATH=$(PROTOUSRSBINDIR):/usr/bin
COMPONENT_TEST_DIR =	$(@D)/tests

# Always show the build and link lines for easier debugging.
COMPONENT_TEST_ARGS +=	V=1

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

# Get the binaries to test from their installed locations.
COMPONENT_SYSTEM_TEST_ENV +=	PATH=/usr/gnu/bin:/usr/bin
COMPONENT_SYSTEM_TEST_DIR =	$(@D)/tests

test:		install $(TEST_64)

system-test:    configure $(SYSTEM_TEST_64)

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
