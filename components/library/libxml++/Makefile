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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libxml++
COMPONENT_VERSION= 2.40.1
COMPONENT_REVISION= 1
COMPONENT_CLASSIFICATION=Development/C++
COMPONENT_FMRI=library/c++/libxml++
COMPONENT_SUMMARY= Library for HTML support in GNOME
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:4ad4abdd3258874f61c2e2a41d08e9930677976d303653cd1670d3e9f35463e9
COMPONENT_ARCHIVE_URL= \
  https://download.gnome.org/sources/$(COMPONENT_NAME)/2.40/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
