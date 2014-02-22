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
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pigz
COMPONENT_VERSION=	2.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://zlib.net/pigz/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:74bbd5962f9420549fc987ddd1ccda692ec2b29d2d612fbbe26edf3fa348ff21
#COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	http://pkgs.fedoraproject.org/repo/pkgs/pigz/$(COMPONENT_ARCHIVE)/042e3322534f2c3d761736350cac303f/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pigz
COMPONENT_TEST_TARGETS=	test

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

PKG_PROTO_DIRS += $(BUILD_DIR_32)

COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"

#ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(BUILD_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
