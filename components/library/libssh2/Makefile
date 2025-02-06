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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2022, Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libssh2
COMPONENT_VERSION=	1.11.1
COMPONENT_SUMMARY=	libssh2 - client-side C library implementing the SSH2 protocol
COMPONENT_PROJECT_URL=	https://www.libssh2.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d9ec76cbe34db98eec3539fe2c899d26b0c837cb3eb466a56b0f109cabf658f7
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_FMRI=	library/libssh2
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Note that static libs are needed to successfully build the tests.
# Many tests fail because docker is needed to run them.
CONFIGURE_OPTIONS += --enable-shared
# Only openssl 1.0 can be found but has 2 more failing tests. Thus, we are using libgcrypt instead.
CONFIGURE_OPTIONS += --with-crypto=libgcrypt

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
