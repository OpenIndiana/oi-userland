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

COMPONENT_NAME=		pixz
COMPONENT_VERSION=	1.0.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://github.com/vasi/pixz/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:af9dac41edd6bf57953471f7fcbd4793810003bf911593ba4c84f7cccb5f74af
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/pixz/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pixz

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

PKG_PROTO_DIRS += $(BUILD_DIR_32)
PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

# Userland default includes -mt which links with libthread which we don't need.
studio_MT =

# pixz's Makefile hard-codes some gcc-only flags in MYCFLAGS and MYLDFLAGS,
# then appends CFLAGS & LDFLAGS to each.  Here we include their preset values
# minus the gcc-only parts, so we can build with Studio.
COMPONENT_BUILD_ARGS += CC="$(CC)"
#COMPONENT_BUILD_ARGS += MYCFLAGS='$(patsubst %,-I%/include,$(LIBPREFIX)) $(OPT)'
#COMPONENT_BUILD_ARGS += MYLDFLAGS='$(patsubst %,-L%/lib,$(LIBPREFIX)) $(OPT)'
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(CC_BITS) -lm"

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(BUILD_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
