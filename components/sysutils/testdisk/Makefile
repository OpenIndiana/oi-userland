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
# Copyright (c) 2016 by Jim Klimov. All rights reserved.
# Copyright (c) 2019 Tim Mooney <Timothy.V.Mooney@gmail.com>
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		testdisk
COMPONENT_VERSION=	7.0
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://www.cgsecurity.org/wiki/TestDisk
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:00bb3b6b22e6aba88580eeb887037aef026968c21a87b5f906c6652cbee3442d
COMPONENT_ARCHIVE_URL=	https://www.cgsecurity.org/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# build with the distribution default libjpeg
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS  +=		--enable-qt

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/$(JPEG_IMPLEM)
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/qt4
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/file-system/ntfsprogs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
