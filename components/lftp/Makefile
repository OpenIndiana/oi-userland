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

COMPONENT_NAME=		lftp
COMPONENT_VERSION=	4.7.6
COMPONENT_PROJECT_URL=	http://lftp.yar.ru/
COMPONENT_ARCHIVE_HASH=	\
    2c8773993ec06f59d7a5734090e64ec37f106f98b250b8c476c55cc0b35aa75d
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)ftp/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1555

TPNO=			34070

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL =   0

# Look for gnutls-3 pkg-config & libraries before the defaults
PKG_CONFIG_PATH.64 := $(PKG_CONFIG_PATH.64)/gnutls-3:$(PKG_CONFIG_PATH.64)
LDFLAGS += -L$(USRLIBDIR64)/gnutls-3

CONFIGURE_OPTIONS  +=		--localedir=$(CONFIGURE_LOCALEDIR)

# Studio 12.4 compiler doesn't grok GNU's __restrict
COMPONENT_BUILD_ARGS +=	CPPFLAGS=-D__restrict=restrict

REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
