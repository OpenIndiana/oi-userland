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

COMPONENT_NAME=		m4
COMPONENT_VERSION=	1.4.17
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f0543c3beb51fa6b3337d8025331591e0e18d8ec2886ed391f1aade43477d508
COMPONENT_BUGDB=	utility/gnu-m4
COMPONENT_ANITYA_ID=	1871

TPNO=			25279

SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_PREFIX =	/usr/gnu
CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)

# The Makefile in the checks directory has different targets for the
# equivalent of "gmake test" and "gmake system-test".

COMPONENT_TEST_DIR =		$(@D)/checks
COMPONENT_TEST_TARGETS =	check-local

COMPONENT_SYSTEM_TEST_DIR =	$(@D)/checks
COMPONENT_SYSTEM_TEST_TARGETS =	installcheck

COMPONENT_TEST_TRANSFORMS += \
	'-e "/PATH=/d"' \
	'-e "/check-them/d"' \
	'-e "/echo m4/d"' \
	'-e "/Leaving directory/d"' \
	'-e "/Entering directory/d"'

REQUIRED_PACKAGES += library/libsigsegv
REQUIRED_PACKAGES += system/library/math
