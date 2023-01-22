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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
# Copyright 2023 Friedrich Kink
#

BUILD_BITS= 64_and_32
BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glibmm
COMPONENT_VERSION=	2.74.0
COMPONENT_SUMMARY=	glibmm - C++ Wrapper for the Glib2 Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:2b472696cbac79db8e405724118ec945219c5b9b18af63dc8cfb7f1d89b0f1fa
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/glibmm/2.74/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gtkmm.org/
COMPONENT_FMRI=		library/c++/glibmm
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS+=		-std=c++17

PATH= $(PATH.gnu)

COMPONENT_TEST_TRANSFORMS = \
	'-e "/^Full log written to/d" ' \
        '-e "s/ [0-9].[0-9][0-9]s//" '

# Build dependency
REQUIRED_PACKAGES += library/desktop/c++/mm-common

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/sigcpp3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
