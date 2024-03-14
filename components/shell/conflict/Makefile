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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		conflict
COMPONENT_VERSION=	2022.10.2
HUMAN_VERSION=		20221002
COMPONENT_SUMMARY=	conflict displays conflicting filenames in your execution path
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_PROJECT_URL=	https://invisible-island.net/conflict/conflict.html
COMPONENT_ARCHIVE_HASH=	sha256:8c183f3cabc814384db94a616d132f252753a8481a3f356a2135691d7d30dffc
COMPONENT_ARCHIVE_URL=	https://invisible-mirror.net/archives/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		shell/conflict
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	BSD-like
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Required to configure correctly.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CC += $(CC_BITS)

# If the configure options are not explicitly set, then configure fails with:
# configure: warning: CC=/ws/onnv-tools/SUNWspro/sunstudio12.1/bin/cc: invalid host type
# configure: warning: CXX=/ws/onnv-tools/SUNWspro/sunstudio12.1/bin/CC: invalid host type
# configure: error: can only configure for one host and one target at a time
CONFIGURE_OPTIONS= --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)

COMPONENT_TEST_DIR= $(BUILD_DIR_64)
COMPONENT_TEST_CMD= ./run_test.sh
COMPONENT_TEST_TARGETS=

# The additional conflict specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
        '-e "s|/tmp/conflict\.......|/tmp/conflict\.xxxxxx|g" ' \
        '-e "s|^\*\*            \$$(@D)/.*$$|XXX_CC_XXX|g" ' \
        '-e "s|^\*\*            /usr/bin/.*$$|XXX_CC_XXX|g" ' \
        '-e "/^XXX_CC_XXX$$/d" '

# Auto-generated dependencies
