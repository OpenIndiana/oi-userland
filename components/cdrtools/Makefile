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

COMPONENT_NAME=         cdrtools
COMPONENT_VERSION=      3.00
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= 	http://sourceforge.net/projects/cdrtools/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6326762da8b8281c9a910c66fe698cd4d1bc5f33c37b59e8f1c83343c25f3e98
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)files/$(COMPONENT_ARCHIVE)/download
PATH=			$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin
COMPONENT_BUGDB=	utility/cdrtools

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_INSTALL_ARGS +=  GMAKE_NOWARN=true
COMPONENT_BUILD_ARGS += GMAKE_NOWARN=true

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
