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

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		unrar
COMPONENT_VERSION=	4.1.4
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_PROJECT_URL=	http://www.rarlabs.com/rar_add.htm
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:705d93285fcd3b9c11f68e52d96395d942bf3c20172dcee14f0d78f1fee57361
COMPONENT_ARCHIVE_URL=	http://www.rarlab.com/rar/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

PKG_PROTO_DIRS = $(MANGLED_DIR)
PKG_PROTO_DIRS += $(BUILD_DIR_32)
PKG_PROTO_DIRS += $(COMPONENT_DIR)

PATCH_LEVEL =	0


CXXFLAGS += "-erroff=wvarhidemem"
COMPONENT_BUILD_ENV += CXX="$(CXX)"
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(studio_NORUNPATH)"
COMPONENT_BUILD_ENV += DEFINES="$(CPP_LARGEFILES)"

COMPONENT_BUILD_ARGS += -f makefile.unix
COMPONENT_BUILD_ARGS += STRIP="/bin/true"

# common targets
build:		$(BUILD_32)

install:	$(BUILD_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
