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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkg-config
COMPONENT_VERSION=	0.23
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/pkg-config
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:08a0e072d6a05419a58124db864f0685e6ac96e71b2875bf15ac12714e983b53
COMPONENT_ARCHIVE_URL=	http://pkgconfig.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pkg-config

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# otherwise our default PKG_CONFIG_PATH will change to the 64-bit libdir
CONFIGURE_LIBDIR.64 =   $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)" 
COMPONENT_TEST_ENV += PATH=/usr/gnu/bin:/usr/bin
ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
