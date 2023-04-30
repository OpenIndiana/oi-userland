#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Gary Mills
# Copyright 2016 Aurelien Larcher
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         xrestop
COMPONENT_VERSION=      0.6
COMPONENT_SUMMARY=      the xrestop X-Resource top utility
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:2e2ec111c4b2798b5dc2dc2b3ec7af4f6b261946e903b8e14db046831d203b29
COMPONENT_ARCHIVE_URL=  https://xorg.freedesktop.org/archive/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.x.org/
COMPONENT_FMRI=         x11/xrestop
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

COMPONENT_PREP_ACTION = ( \
	cd $(@D) && \
	$(MKDIR) m4 && \
	libtoolize --copy --force && \
	aclocal -I m4 && \
	automake -c -f -a && \
	autoconf )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxres
