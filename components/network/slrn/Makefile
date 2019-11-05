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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		slrn
COMPONENT_VERSION=	1.0.1
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://slrn.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:06b4a060939ec3077e5a060c7a2556747c96061a24eec2c09e1feacd5dbeaae6
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/slrn/files/slrn/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)
CONFIGURE_SCRIPT = $(@D)/configure

# slrn configure test for 'mkdir -p' functionality doesn't like Solaris
# implementation (GNU mkdir will understand --version option).
PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--with-server-file=/etc/nntpserver
CONFIGURE_OPTIONS +=	--with-slrnpull=/var/spool/slrnpull
CONFIGURE_OPTIONS +=	--enable-spool
CONFIGURE_OPTIONS +=	--with-ssl

# Needed to successfully link the 64-bit programs.
CC +=			$(CC_BITS)

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/slang
REQUIRED_PACKAGES += system/library
