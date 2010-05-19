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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#
include ../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		file
COMPONENT_VERSION=	5.0.4
COMPONENT_DESCRIPTION=	"command and library to determine file type"
COMPONENT_SRC=		$(COMPONENT_NAME)-5.04
COMPONENT_COPYRIGHT=	$(COMPONENT_SRC)/COPYING
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	56ddf7135471aa656334ed8fefe1112bcccc2cc3
COMPONENT_ARCHIVE_URL=	ftp://ftp.fu-berlin.de/unix/tools/file/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/archive-libraries-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)
