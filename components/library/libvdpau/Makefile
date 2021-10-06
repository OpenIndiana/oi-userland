#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016-2020 Aurelien Larcher
#
BUILD_BITS=32_and_64
BUILD_STYLE=meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvdpau
COMPONENT_VERSION=	1.4
COMPONENT_SUMMARY=	VDPAU libaries and headers
COMPONENT_PROJECT_URL=	http://freedesktop.org/wiki/Software/VDPAU/
COMPONENT_FMRI=		library/graphics/libvdpau
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:4258824c5a4555ef31de0a7d82b3caf19e75a16a13949f1edafc5f6fb2d33f30	
COMPONENT_ARCHIVE_URL=	https://gitlab.freedesktop.org/vdpau/libvdpau/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

unexport SHELLOPTS

# When running the tests an accelerated graphics device is needed (Xlib needs NV-GLX extension)
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "s/      [0-9].[0-9][0-9] s//" ' \
	'-e "/OK/p" ' \
	'-e "/Ok/p" ' \
	'-e "/Fail/p" ' \
	'-e "/Pass/p" ' \
	'-e "/Skipped/p" ' \
	'-e "/Timeout/p" ' \
	'-e "/ok/p" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
