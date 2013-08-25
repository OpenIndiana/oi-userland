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
# Copyright (c) 2013 David Hoeppner. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgee
COMPONENT_VERSION=	0.8.6
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Libgee
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:cf9188b225a4e4b84696a13e5f9af0af0aa19a9ed05d01d1161023069f5be3d6
COMPONENT_ARCHIVE_URL=	http://download.gnome.org/sources/libgee/0.8/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libgee

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--enable-shared

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
