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
COMPONENT_VERSION=	7.1
COMPONENT_REVISION= 1
COMPONENT_PROJECT_URL=	https://www.cgsecurity.org/wiki/TestDisk
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:1413c47569e48c5b22653b943d48136cb228abcbd6f03da109c4df63382190fe
COMPONENT_ARCHIVE_URL=	https://www.cgsecurity.org/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

# build with the distribution default libjpeg
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

QT5_ROOT=/usr/lib/qt/5.15
PATH=$(PATH.gnu):$(QT5_BINDIR)
PKG_CONFIG_PATH=$(PKG_CONFIG_PATH.$(BITS)):$(QT5_PKG_CONFIG_PATH)
LD_OPTIONS += -L$(QT5_LIBDIR) -R$(QT5_LIBDIR)

CONFIGURE_OPTIONS += --enable-qt

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/file-system/ntfsprogs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += sysutils/e2fsprogs
