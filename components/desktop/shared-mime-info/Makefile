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
# Copyright 2022 Andreas Wacknitz.  All rights reserved.
#
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= shared-mime-info
COMPONENT_VERSION= 2.3
COMPONENT_SUMMARY= application/MIME type registry
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:96ac085d82e2e654e40e34c13d97b74f6657357ee6b443d922695adcf548961c
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/Software/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_URL=	https://gitlab.freedesktop.org/xdg/$(COMPONENT_NAME)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= desktop/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += -Dupdate-mimedb=true

COMPONENT_TEST_TRANSFORMS += \
	' -e "s/ [0-9]*\.[0-9]*s//" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
