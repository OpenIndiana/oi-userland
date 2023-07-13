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
BUILD_BITS=			32_and_64
USE_OPENSSL11=			yes
USE_DEFAULT_TEST_TRANSFORMS=	yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libssh2
COMPONENT_VERSION=	1.10.0
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://www.libssh2.org/
COMPONENT_SUMMARY=	libssh2 - client-side C library implementing the SSH2 protocol
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:2d64e90f3ded394b91d3a2e774ca203a4179f69aebee03003e5a6fa621e41d51
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/libssh2
COMPONENT_LICENSE=	BSD
COMPONENT_CLASSIFICATION= System/Security

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=   --enable-shared
CONFIGURE_OPTIONS +=   --disable-static
CONFIGURE_OPTIONS +=   --with-libssl-prefix=/usr/openssl/1.1

# Test suite needs this
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
