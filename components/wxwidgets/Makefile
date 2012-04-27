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

COMPONENT_NAME=		wxGTK
COMPONENT_VERSION=	2.8.12
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:13cf89f2c29bcb90bb56a31ac1af10f23003d3d43c3e4b24991518f5dc4e5abe
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/wxwindows/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.wxwidgets.org/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKG_PROTO_DIRS += $(COMPONENT_DIR)/man

# We need to compile with /usr/lib/$(MACH64)/glib-2.0
# https://defect.opensolaris.org/bz/show_bug.cgi?id=9957
$(BUILD_64): CONFIGURE_OPTIONS += PKG_CONFIG_PATH=/usr/lib/$(MACH64)/pkgconfig

# get rid of compiler path set in RUNPATH
LDFLAGS += $(studio_NORUNPATH)
LDFLAGS += $(CC_BITS)
LDFLAGS += $(studio_CXXLIB_CSTD)

CXXFLAGS += $(studio_XREGS)

CONFIGURE_OPTIONS += --with-gtk
CONFIGURE_OPTIONS += --enable-gtk2
CONFIGURE_OPTIONS += --enable-unicode
CONFIGURE_OPTIONS += --enable-mimetype
CONFIGURE_OPTIONS += --enable-gui
CONFIGURE_OPTIONS += --enable-xrc
CONFIGURE_OPTIONS += --with-subdirs
CONFIGURE_OPTIONS += --with-expat
CONFIGURE_OPTIONS += --with-sdl
CONFIGURE_OPTIONS += --without-gnomeprint
CONFIGURE_OPTIONS += --without-gnomevfs
CONFIGURE_OPTIONS += --with-opengl
CONFIGURE_OPTIONS += --without-libmpack
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"

include ../../make-rules/shared-targets.mk

# I want to use userland's "build" target in contrib subdirectory, but I need
# to skip the configure phase
$(BUILD_DIR_32)/contrib/.configured \
$(BUILD_DIR_64)/contrib/.configured:
	$(TOUCH) $@

# common targets
build:		$(BUILD_32_and_64) \
		$(BUILD_DIR_32)/contrib/.built \
		$(BUILD_DIR_64)/contrib/.built

install:	$(INSTALL_32_and_64) \
		$(BUILD_DIR_32)/contrib/.installed \
		$(BUILD_DIR_64)/contrib/.installed

test: 		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
