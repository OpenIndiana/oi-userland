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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		coreutils
COMPONENT_VERSION=	8.26
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:155e94d748f8e2bc327c66e0cbebdb8d6ab265d2f37c3c928f7bf6c3beba9a8e
COMPONENT_BUGDB=	utility/gnu-coreutils
COMPONENT_ANITYA_ID=	343

TPNO=			32865

TEST_TARGET= install $(TEST_64)
SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

# We need the GNU grep command to configure/build.
PATH=$(GNUBIN):$(USRBINDIR)

PATCH_LEVEL=		0

CPPFLAGS += -I$(USRINCDIR)/gmp
CONFIGURE_PREFIX	 =	$(USRGNUDIR)
CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)

# Recreate configure and Makefile to pick up changes in .../src/local.mk
COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f && automake)

# Needed to get tests to work when run directly from the tests subdirectory.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=		V=1

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

# Master test results are different between x86 and SPARC (different # of
# tests run).
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

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

REQUIRED_PACKAGES += library/gmp
