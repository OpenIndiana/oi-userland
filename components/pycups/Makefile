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

COMPONENT_NAME=		pycups
COMPONENT_VERSION=	1.9.46
COMPONENT_DESCRIPTION=	"Python language bindings for CUPS"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://cyberelk.net/tim/software/pycups/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:3d58a0f7b4a1b6a2880baf9ef5e14eae461d0982
COMPONENT_ARCHIVE_URL=	http://cyberelk.net/tim/data/pycups/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/setup.py.mk
include ../../make-rules/ips.mk

PYTHON_ENV +=	CFLAGS=-DVERSION=\\\"$(COMPONENT_VERSION)\\\"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)
