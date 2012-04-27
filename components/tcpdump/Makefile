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

COMPONENT_NAME=		tcpdump
COMPONENT_VERSION=	4.1.1
COMPONENT_PROJECT_URL=	http://www.tcpdump.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e6cd4bbd61ec7adbb61ba8352c4b4734f67b8caaa845d88cb826bc0b9f1e7f0a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)release/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# the default setting of 8s makes us core dump
studio_ALIGN.sparc.32=

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --enable-ipv6=yes
CONFIGURE_OPTIONS += --with-user=nobody
CONFIGURE_OPTIONS += --without-crypto

# common targets
build:          $(BUILD_32)

install:        $(INSTALL_32) 

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk

