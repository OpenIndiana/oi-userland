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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libconfuse
COMPONENT_VERSION=	2.6
COMPONENT_SRC_NAME=	confuse
COMPONENT_PROJECT_URL=	http://www.nongnu.org/confuse/
COMPONENT_ARCHIVE_HASH=	\
    sha256:e8d653159b152f3850a7224b3eb604955795dbd3fd6603816ee46411ea53e84a
COMPONENT_ARCHIVE_URL=	http://bzero.se/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libconfuse

TPNO=			6306

TEST_TARGET= install $(TEST_32_and_64)
SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared

# This is really only needed to get the test target to pass.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_TEST_DIR =		$(@D)/tests

COMPONENT_SYSTEM_TEST_DIR =	$(@D)/tests

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional libconfuse specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

# Needed to build the test programs.
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	(cd $(@D)/src ; $(GMAKE) libconfuse.la )

# Get correct libconfuse.so.0 from the proto area.
TEST_LIBPATH.32 =       $(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =       $(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=   LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

ASLR_MODE = $(ASLR_ENABLE)
