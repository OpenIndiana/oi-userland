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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		unrar
COMPONENT_VERSION=	5.6.8
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_SUMMARY=	Rar archives extractor utility
COMPONENT_PROJECT_URL=	http://www.rarlabs.com/rar_add.htm
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:a4cc0ac14a354827751912d2af4a0a09e2c2129df5766576fa7e151791dd3dff
COMPONENT_ARCHIVE_URL=	http://www.rarlab.com/rar/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	archiver/unrar
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE= UnRAR

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

PKG_PROTO_DIRS = $(MANGLED_DIR)
PKG_PROTO_DIRS += $(BUILD_DIR_64)
PKG_PROTO_DIRS += $(COMPONENT_DIR)

# Needed by .../unrar/os.hpp to correctly define platform endianness.
CXXFLAGS.i386 = -DLITTLE_ENDIAN
CXXFLAGS.sparc = -DBIG_ENDIAN
CXXFLAGS += $(CXXFLAGS.$(MACH))
COMPONENT_BUILD_ENV += CXX="$(CXX)"
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV += DEFINES="$(CPP_LARGEFILES)"

COMPONENT_BUILD_ARGS += STRIP="/bin/true"

# common targets
build:		$(BUILD_64)

install:	$(BUILD_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
