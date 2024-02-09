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
# Copyright 2019 Nona Hansel
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         rarian
COMPONENT_VERSION=      0.8.5
COMPONENT_SUMMARY=      Documentation meta-data library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:93cf05e6bf51af169d0b32a2dc03f9a0f7895cae4e58b1a9b75777c040e9be0f
COMPONENT_ARCHIVE_URL=	https://gitlab.freedesktop.org/$(COMPONENT_NAME)/$(COMPONENT_NAME)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://rarian.freedesktop.org
COMPONENT_FMRI=			text/rarian
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPLv2, GPLv2

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D) && NOCONFIGURE=1 ./autogen.sh )

LD_OPTIONS=

CONFIGURE_OPTIONS += --localstatedir=/var 
CONFIGURE_OPTIONS += --disable-skdb-update
CONFIGURE_OPTIONS += --with-convert-dir=/usr/share/omf

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/tinyxml
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
