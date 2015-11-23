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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

BITS=64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		conflict
COMPONENT_VERSION=	20140723
IPS_COMPONENT_VERSION=	0.2014.7.23
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_PROJECT_URL=	http://invisible-island.net/conflict/conflict.html
COMPONENT_ARCHIVE_HASH=	\
    sha256:2ef48ef4c3e2b26eb2de7748ff07e296de3ab7a4437540d60e1fdf321fc5c943
COMPONENT_ARCHIVE_URL=	ftp://invisible-island.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/conflict

TPNO=			21547

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Required to configure correctly.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

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

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# We really do need to build conflict so that it can use the files in the
# build directory. We are using the installed conflict binary to do this
# though when we run the system tests.
system-test:    build $(SYSTEM_TEST_64)


REQUIRED_PACKAGES += system/library
