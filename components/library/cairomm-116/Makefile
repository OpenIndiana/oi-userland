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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

# This is cairomm-1.16 ABI series

COMPONENT_NAME=			cairomm
COMPONENT_VERSION=		1.18.0
COMPONENT_SUMMARY=		C++ wrapper for the cairo graphics library
COMPONENT_PROJECT_URL=		https://cairographics.org/cairomm/
COMPONENT_FMRI=			library/desktop/c++/cairomm-116
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=		https://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:b81255394e3ea8e8aa887276d22afa8985fc8daef60692eb2407d23049f03cfb
COMPONENT_LICENSE=		LGPL-2.0-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/sigcpp3
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += system/library
