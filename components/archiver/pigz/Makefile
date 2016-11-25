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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2016, Jim Klimov
# Copyright 2016 Gary Mills
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pigz
#
# Version 2.3.3 is no longer available
COMPONENT_VERSION=	2.3.4
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://zlib.net/pigz/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6f031fa40bc15b1d80d502ff91f83ba14f4b079e886bfb83221374f7bf5c8f9a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pigz
COMPONENT_TEST_TARGETS=	test

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -std=c99
LDFLAGS += -lz

CFLAGS += $(CPP_LARGEFILES)

PKG_PROTO_DIRS += $(BUILD_DIR_32)

COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"

#ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(BUILD_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
