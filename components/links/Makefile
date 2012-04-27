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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		links
COMPONENT_VERSION=	1.03
IPS_COMPONENT_VERSION=	1.0.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://jikos.cz/~mikulas/links/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:32443c6f011216a8a43ed0806d9d23c1defdd19bc4b021ee00cda197782e175a
COMPONENT_ARCHIVE_URL=	http://www.jikos.cz/~mikulas/$(COMPONENT_NAME)/download/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Configure in links does not understand CC, CXX, etc.  Need to generate a
# new configure for it to configure and build properly.
COMPONENT_PREP_ACTION=	(cd $(@D) ; autoconf) 

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS) -xstrconst -Dinline"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:	$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
