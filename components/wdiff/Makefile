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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wdiff
COMPONENT_VERSION=	1.2.2
COMPONENT_ARCHIVE_HASH=	\
    sha256:34ff698c870c87e6e47a838eeaaae729fa73349139fc8db12211d2a22b78af6b
COMPONENT_ANITYA_ID=	5112

TPNO=			21556

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_OPTIONS +=	--enable-experimental

# Used directly as a macro in C code, so literal quotes must be left intact.
CFLAGS +=	-DDIFF_PROGRAM=\\\"$(GDIFF)\\\"

COMPONENT_TEST_DIR =		$(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =		./testsuite
COMPONENT_TEST_ARGS =		AUTOTEST_PATH="src"
COMPONENT_TEST_TARGETS =

COMPONENT_SYSTEM_TEST_DIR =	$(SOURCE_DIR)/tests
COMPONENT_SYSTEM_TEST_CMD =	./testsuite
COMPONENT_SYSTEM_TEST_ARGS =	AUTOTEST_PATH="src"
COMPONENT_SYSTEM_TEST_TARGETS =

# Get wdiff from /usr/bin
COMPONENT_SYSTEM_TEST_ENV +=   PATH="$(USRBINDIR)"

REQUIRED_PACKAGES += text/gnu-diffutils
