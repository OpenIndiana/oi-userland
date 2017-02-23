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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libssh2
COMPONENT_VERSION=	1.7.0
COMPONENT_PROJECT_URL=	http://www.libssh2.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:e4561fd43a50539a8c2ceb37841691baf03ecb7daf043766da1b112e4280d584
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libssh2
COMPONENT_ANITYA_ID=	1730

TPNO=			27245

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=   --enable-shared
CONFIGURE_OPTIONS +=   --disable-static

# Adjust the .so line in the libssh2_sftp_fstatvfs man page to correctly find
# the file it references (as we place it in the man3ssh2 section on Solaris).
#
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i -e 's|3|3ssh2|g' \
		$(PROTOUSRSHAREMAN3DIR)/libssh2_sftp_fstatvfs.3;

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS 

# Master test results are the same for both 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional libssh2 specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
        '-e "s|^.*make.*$$|XXX_CC_XXX|g" ' \
        '-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
        '-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

# Just run "gmake check" from the tests directory.
COMPONENT_TEST_DIR =		$(BUILD_DIR_$(BITS))/tests
COMPONENT_SYSTEM_TEST_DIR =	$(BUILD_DIR_$(BITS))/tests

# Adjust how the simple test program is built.
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	$(GSED) -e "s|^simple_DEPENDENCIES.*$$|simple_DEPENDENCIES =|" \
		-e "s|^LDADD.*$$|LDADD = -lssh2|" \
		$(BUILD_DIR_$(BITS))/tests/Makefile \
		> $(BUILD_DIR_$(BITS))/tests/Makefile-system-test

COMPONENT_SYSTEM_TEST_ENV = \
	AM_MAKEFLAGS="-f $(BUILD_DIR_$(BITS))/tests/Makefile-system-test"
COMPONENT_SYSTEM_TEST_ARGS = -f $(BUILD_DIR_$(BITS))/tests/Makefile-system-test

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
