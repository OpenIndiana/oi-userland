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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=/usr/xpg4/bin:/usr/bin

COMPONENT_NAME=		ejabberd
COMPONENT_VERSION=	2.1.8
COMPONENT_PROJECT_URL=	http://www.ejabberd.im/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:dedf7684f9e96efbbc12f08f175096ef50b3f75b284bd27d172eaf75cecded7f
COMPONENT_ARCHIVE_URL=	http://www.process-one.net/downloads/ejabberd/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk

SRC_OFFSET =	src
# Now we override paths to .built
BUILD_DIR_32 = $(BUILD_DIR)/$(MACH32)/$(SRC_OFFSET)

include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# tail with -n is needed
CONFIGURE_ENV += "PATH=/usr/xpg4/bin:/usr/bin"

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--with-erlang=$(USRBINDIR)
CONFIGURE_OPTIONS +=	--localstatedir=/var

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(BUILD_DIR)/$(MACH32))

CONFIGURE_SCRIPT = ./configure

build:	$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
