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
# Copyright (c) 2014 Alexander Pyhalov
# Copyright (c) 2015 Aurelien Larcher
# Copyright (c) 2018 Michal Nowak
#

BUILD_BITS=	64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=          libcompizconfig
COMPONENT_VERSION=       0.8.18
COMPONENT_FMRI=          desktop/compiz/library/libcompizconfig
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_PROJECT_URL=   http://www.northfield.ws
COMPONENT_SUMMARY=       compizconfig libraries - is an alternative configuration system for compiz
COMPONENT_SRC=           $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=       $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:917f0cd146a97a42781366b7c992ef5a4ea62ca68247d977293bb1bdd932fcde
COMPONENT_ARCHIVE_URL= \
    http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=    GPLv2

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+=    --sysconfdir=/etc
CONFIGURE_OPTIONS+=    --disable-static

# Build dependencies
REQUIRED_PACKAGES += desktop/compiz

# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/protobuf
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += x11/library/libx11
