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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
# 32-bit preferred as only *-config and source generation scripts delivered.
BUILD_BITS= 32_and_64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wxWidgets
COMPONENT_VERSION=	3.0.2
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:346879dc554f3ab8d6da2704f651ecb504a22e9d31c17ef5449b129ed711585d
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/wxwindows/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.wxwidgets.org/
COMPONENT_BUGDB=	library/wxwidgets

TPNO=			28307

CXXFLAGS += -std=c++11

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PKG_PROTO_DIRS += $(COMPONENT_DIR)/man

LDFLAGS += $(CC_BITS)

CONFIGURE_OPTIONS += --with-gtk=2
CONFIGURE_OPTIONS += --enable-mimetype
CONFIGURE_OPTIONS += --enable-xrc
CONFIGURE_OPTIONS += --with-subdirs
CONFIGURE_OPTIONS += --with-expat
CONFIGURE_OPTIONS += --with-sdl
CONFIGURE_OPTIONS += --without-gnomeprint
CONFIGURE_OPTIONS += --without-gnomevfs
CONFIGURE_OPTIONS += --with-opengl
CONFIGURE_OPTIONS += --without-libmpack

ASLR_MODE =   $(ASLR_ENABLE)

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxxf86vm
