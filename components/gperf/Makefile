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
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gperf
COMPONENT_VERSION=	3.0.4
COMPONENT_ARCHIVE_HASH=	\
    sha256:767112a204407e62dbc3106647cf839ed544f3cf5d0f0523aaa2508623aad63e

TPNO=			28116

# must build tests before use
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=	--docdir=$(USRSHAREDOCDIR)/gperf

# test/system-test is tricky.
#    Reason being is this component bundles! test results
#    with the source and those results are compared against
#    generated results.
#    Unfortunately these test results embed the string:
#    /* Command-line: ../src/gperf -L C -F ', 0, 0' -j1 -i 1 -g
#    which contains the actual command run: ../src/gperf
#    That string is correct for test but system-test will have /usr/bin/gperf
#    do a sed is run over the bundled test results with /usr/bin/gperf
#    so that an internal compare will pass.
#    Put another way this component does internally what the userland
#    test infrastructure is doing.

# modify bundled test results for system-test
COMPONENT_PRE_SYSTEM_TEST_ACTION = \
	($(GSED) -i -e "s|../src/gperf|/usr/bin/gperf|" \
		$(SOURCE_DIR)/tests/*.exp)

COMPONENT_SYSTEM_TEST_ARGS = GPERF=$(USRBINDIR)/gperf

# normalize the name of gperf
# remove compilation lines
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|../src/gperf|gperf|g" ' \
	'-e "s|/usr/bin/gperf|gperf|g" ' \
	'-e "s|^.*$(CC).*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
