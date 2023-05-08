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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2018 Michal Nowak
#

BUILD_STYLE= meson
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pangomm
COMPONENT_MAJOR_VERSION=	2.46
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).3
COMPONENT_SUMMARY=	pangomm - C++ Wrapper for the pango Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:410fe04d471a608f3f0273d3a17d840241d911ed0ff2c758a9859c66c6f24379
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/pangomm/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gtkmm.org/
COMPONENT_FMRI=		library/desktop/c++/pangomm
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CXXFLAGS += -std=c++11

# I haven't found the reason yet why generating the documentation differs from my systems to the build server.
# So we won't build documentation for now as it increases the package size significantely. 
CONFIGURE_OPTIONS += -Dbuild-documentation=false

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
