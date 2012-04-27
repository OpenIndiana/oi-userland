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

COMPONENT_NAME=		bcc
COMPONENT_VERSION=	0.16.17
COMPONENT_PROJECT_URL=	http://homepage.ntlworld.com/robert.debath/dev86/
COMPONENT_SRC=		dev86-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	Dev86src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:52ed4980c0e4b68d2624aadb0ceb0339cb3fd8dd7c2175419d4f77a451846cbe
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPILER=gcc

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Create the Makefile before we build
COMPONENT_PRE_BUILD_ACTION = (cd $(@D) ; CC="$(CC)" $(GMAKE) make.fil)
# build with the created Makefile (make.fil)
COMPONENT_BUILD_ARGS = -f make.fil
COMPONENT_BUILD_ARGS += PATH="$(@D)/bin:$(PATH)"
COMPONENT_BUILD_ARGS += MAKE="$(GMAKE)"
COMPONENT_BUILD_ARGS += VERSION="$(COMPONENT_VERSION)"
COMPONENT_BUILD_ARGS += TOPDIR="$(@D)"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_TARGETS = bcc86 as86 ld86 ar86


# common targets
install build:		$(BUILD_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
