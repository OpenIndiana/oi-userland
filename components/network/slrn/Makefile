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
# Copyright (c) 2019 Nona Hansel
#

BUILD_BITS= 64
#USE_OPENSSL11= yes		slrn doesn't seem to be compatible with openssl-1.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		slrn
COMPONENT_VERSION=	1.0.3
HUMAN_VERSION=		1.0.3a
COMPONENT_SUMMARY=	slrn is an text-based news client
COMPONENT_PROJECT_URL=	https://slrn.info
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(HUMAN_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:3ba8a4d549201640f2b82d53fb1bec1250f908052a7983f0061c983c634c2dac
COMPONENT_ARCHIVE_URL=	https://jedsoft.org/releases/slrn/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		network/nntp/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)

CONFIGURE_SCRIPT = $(@D)/configure

# slrn configure test for 'mkdir -p' functionality doesn't like Solaris
# implementation (GNU mkdir will understand --version option).
PATH=$(PATH.gnu)

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--with-server-file=/etc/nntpserver
CONFIGURE_OPTIONS +=	--with-slrnpull=/var/spool/slrnpull
CONFIGURE_OPTIONS +=	--enable-spool
CONFIGURE_OPTIONS +=	--with-ssl=$(OPENSSL_PREFIX)

ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/slang
REQUIRED_PACKAGES += system/library
