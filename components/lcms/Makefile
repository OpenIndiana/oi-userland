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

COMPONENT_NAME=		lcms
COMPONENT_VERSION=	1.19
COMPONENT_DESCRIPTION=	"Little Color Management System"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	4f192cfd36d8b819e6885571401f949220609005
COMPONENT_ARCHIVE_URL=	http://www.littlecms.com/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/archive-libraries-drop
PKGMOGRIFY_TRANSFORMS +=	$(WS_TOP)/transforms/libtool-drop

# additional preparation after unpacking and patching
COMPONENT_PREP_ACTION=	$(RM) $(@D)/include/icc34.h

# common targets
build:		$(COMPONENT_SRC)/build-32/.built \
		$(COMPONENT_SRC)/build-64/.built

install:	$(COMPONENT_SRC)/build-32/.installed \
		$(COMPONENT_SRC)/build-64/.installed

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)
