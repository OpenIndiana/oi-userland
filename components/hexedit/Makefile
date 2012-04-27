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

COMPONENT_NAME=		hexedit
COMPONENT_VERSION=	1.2.12
COMPONENT_PROJECT_URL=	http://merd.sourceforge.net/pixel/hexedit.html
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).src.tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bcffbf3d128516cc4e1da64485866fbb5f62754f2af8327e7a527855186ba10f
COMPONENT_ARCHIVE_URL=	http://rigaux.org/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =  \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS += "-Dinline"

CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
