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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

# for ginstall and tail -n
PATH=/usr/gnu/bin:/usr/bin

COMPONENT_NAME=		ejabberd
COMPONENT_VERSION=	2.1.13
COMPONENT_PROJECT_URL=	http://www.ejabberd.im/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a80d1c72e435da31758261cb0c04fe750ac71fc3e33a3b606123efd3b3abc86d
COMPONENT_ARCHIVE_URL=	http://www.process-one.net/downloads/ejabberd/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/ejabberd

include $(WS_MAKE_RULES)/prep.mk

SRC_OFFSET =	src
# Now we override paths to .built
BUILD_DIR_32 = $(BUILD_DIR)/$(MACH32)/$(SRC_OFFSET)

COMPONENT_PREP_ACTION = \
       (cd $(@D)/src ; PATH=$(PATH) $(AUTORECONF) -fiv)


include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += "HOME=/tmp"
CONFIGURE_ENV += "HOME=/tmp"
COMPONENT_INSTALL_ENV += "HOME=/tmp"

CONFIGURE_SCRIPT = $(SOURCE_DIR)/src/configure
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(BUILD_DIR)/$(MACH32))

# tail with -n is needed
CONFIGURE_ENV += "PATH=/usr/xpg4/bin:/usr/bin"

CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--with-erlang=$(USRBINDIR)
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--enable-odbc

COMPONENT_BUILD_TARGETS = all

build:	$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
