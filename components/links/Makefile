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
# Because the Studio compiler generates thousands of lines of warnings.
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		links
COMPONENT_VERSION=	2.14
COMPONENT_PROJECT_URL=	http://links.twibright.com/
COMPONENT_ARCHIVE_HASH=	\
    sha256:22fa8dcb5a60b8ffd611de31ebd4c79edce472637a3554bab401795da91d4387
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1822

TPNO=			34022

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL =		0

# Configure in links does not understand CC, CXX, etc.  Need to generate a
# new configure for it to configure and build properly.
COMPONENT_PREP_ACTION=	(cd $(@D) ; autoconf)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += library/zlib
