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
# Copyright (c) 2023 Andreas Wacknitz
# Copyright (c) 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=          libcompizconfig
COMPONENT_VERSION=       0.8.18
COMPONENT_REVISION=      3
COMPONENT_SUMMARY=       compizconfig libraries - is an alternative configuration system for compiz
COMPONENT_PROJECT_URL=   https://compiz-fusion.org/
COMPONENT_SRC=           $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=       $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH=  sha256:ae41fee04d526b35d7ee3408111782e498a89fd598a101e0f8da0330f652626a
COMPONENT_ARCHIVE_URL=   https://gitlab.com/compiz/$(COMPONENT_NAME)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=          desktop/compiz/library/libcompizconfig
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=       GPLv2
COMPONENT_LICENSE_FILE=  COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# The source folder contains a commit hash, remove it:
COMPONENT_POST_UNPACK_ACTION = ( $(MV) $(COMPONENT_NAME)-v$(COMPONENT_VERSION)-* $(COMPONENT_SRC) )

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f -i)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static

# Build dependencies
REQUIRED_PACKAGES += desktop/compiz

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/abseil-cpp
REQUIRED_PACKAGES += library/c++/protobuf
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
