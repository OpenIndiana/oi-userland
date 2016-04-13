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

COMPONENT_NAME = libneon
COMPONENT_VERSION = 0.29.6
COMPONENT_REVISION = 1
COMPONENT_PROJECT_URL=	http://www.webdav.org/neon/
COMPONENT_SRC_NAME = neon
COMPONENT_SRC = $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = \
    sha256:9c640b728d6dc80ef1e48f83181166ab6bc95309cece5537e01ffdd01b96eb43
COMPONENT_ARCHIVE_URL = $(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/neon

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0

CC += $(CC_BITS)
CPPFLAGS += $(CPP_LARGEFILES)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --mandir=/usr/share/man
CONFIGURE_OPTIONS += --infodir=/usr/share/info
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-webdav
CONFIGURE_OPTIONS += --enable-threadsafe-ssl=posix
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-warnings
CONFIGURE_OPTIONS += --disable-ld-version-script
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --with-ssl=openssl
CONFIGURE_OPTIONS += --with-libproxy
CONFIGURE_OPTIONS += --with-libxml2

COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

