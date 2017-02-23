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

COMPONENT_NAME=		sed
COMPONENT_VERSION=	4.2.2
COMPONENT_ARCHIVE_HASH=	\
    sha256:fea0a94d4b605894f3e2d5572e3f96e4413bcad3a085aae7367c2cf07908b2ff
COMPONENT_BUGDB=	utility/gnu-sed
COMPONENT_ANITYA_ID=	4789

TPNO=			12595

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_BINDIR.64= $(GNUBIN)

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)

COMPONENT_TEST_DIR =		$(@D)/testsuite

COMPONENT_TEST_TRANSFORMS += \
    '-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Nothing to be.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^/usr/gnu/bin/make.*$$|XXX_CC_XXX|g" ' \
    '-e "/^XXX_CC_XXX$$/d" '

# Modify test results for system-test
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	($(GSED) -i -e "s|../sed/sed|/usr/gnu/bin/sed|" \
                $(@D)/testsuite/version.good) ;
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	($(GSED) -i -e "s|../sed/sed|/usr/gnu/bin/sed|" \
                $(SOURCE_DIR)/testsuite/eval.good) ;
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	($(GSED) -i -e "s|../sed/sed|/usr/gnu/bin/sed|" \
                $(SOURCE_DIR)/testsuite/eval.sed) ;

COMPONENT_SYSTEM_TEST_ENV +=	SED=$(GNUBIN)/sed
COMPONENT_SYSTEM_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"
COMPONENT_SYSTEM_TEST_DIR =	$(@D)/testsuite
