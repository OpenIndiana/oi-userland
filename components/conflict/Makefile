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
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		conflict
COMPONENT_VERSION=	20150705
IPS_COMPONENT_VERSION=	0.2015.7.5
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_PROJECT_URL=	http://invisible-island.net/conflict/conflict.html
COMPONENT_ARCHIVE_HASH=	\
    sha256:30e14808768a938df139a1b76f8f7397e1b3bf46a18ceabcc8b1b1a70d5ea8a9
COMPONENT_ARCHIVE_URL=	ftp://invisible-island.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13297

TPNO=			27130

# We really do need to build conflict so that it can use the files in the
# build directory. We are using the installed conflict binary to do this
# though when we run the system tests.
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

# Required to configure correctly.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_TEST_DIR =	$(BUILD_DIR_64)
COMPONENT_TEST_CMD =	./run_test.sh
COMPONENT_TEST_TARGETS =

# The additional conflict specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|/tmp/conflict\.......|/tmp/conflict\.xxxxxx|g" ' \
	'-e "s|^\*\*		\$$(@D)/.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^\*\*		/usr/bin/.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

COMPONENT_SYSTEM_TEST_DIR =	$(BUILD_DIR_64)
COMPONENT_SYSTEM_TEST_ENV =	CONFLICT_BIN=/usr/bin/conflict
COMPONENT_SYSTEM_TEST_CMD =	./run_test.sh
COMPONENT_SYSTEM_TEST_TARGETS =
