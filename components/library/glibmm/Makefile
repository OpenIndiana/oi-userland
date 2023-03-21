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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glibmm
COMPONENT_VERSION=	2.66.6
COMPONENT_SUMMARY=	glibmm - C++ Wrapper for the Glib2 Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:5358742598181e5351d7bf8da072bf93e6dd5f178d27640d4e462bc8f14e152f
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/glibmm/2.66/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gtkmm.org/
COMPONENT_FMRI=		library/c++/glibmm
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += -Dbuild-documentation=true

COMPONENT_TEST_TRANSFORMS += ' -e "s/[0-9]*\.[0-9]*s/X.XXs/" '

# Build dependency
REQUIRED_PACKAGES += library/desktop/c++/mm-common

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
