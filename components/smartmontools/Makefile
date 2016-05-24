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
# Copyright (c) 2014 Nexenta Systems, Inc.  All rights reserved.

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		smartmontools
COMPONENT_VERSION=	6.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://downloads.sourceforge.net/smartmontools
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:486f660579bb0fb4f6b927ded7531cb1f99685c666397377761c5b04dd96065b
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/smartmontools/files/smartmontools/6.2/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS +=	--enable-attributelog
CONFIGURE_OPTIONS +=	--enable-savestates
CONFIGURE_OPTIONS +=	--enable-drivedb
CONFIGURE_OPTIONS +=	--with-savestates=/var/lib/smartmontools/smartd.
CONFIGURE_OPTIONS +=	--with-attributelog=/var/lib/smartmontools/attrlog.


build:		$(BUILD_32)

test:		$(TEST_32)

install:	$(INSTALL_32)

