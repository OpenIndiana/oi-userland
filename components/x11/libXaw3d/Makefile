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
# Copyright 2018 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           libXaw3d
COMPONENT_VERSION=        1.6.3
COMPONENT_FMRI=           x11/library/toolkit/libxaw3d
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY= libXaw3d - X Athena Widgets library with 3-D styled widgets
COMPONENT_SRC=     $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2dba993f04429ec3d7e99341e91bf46be265cc482df25963058c15f1901ec544
COMPONENT_ARCHIVE_URL= \
  https://www.x.org/releases/individual/lib/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.x.org/
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) &&  autoreconf -f  -i )

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += x11/header/xproto
REQUIRED_PACKAGES += x11/header/xextproto

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
