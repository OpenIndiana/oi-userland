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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=         libdmx
COMPONENT_VERSION=      1.1.4
COMPONENT_SUMMARY=      X Window System DMX (Distributed Multihead X) extension library
COMPONENT_PROJECT_URL=  $(XORG_PROJECT_URL)
COMPONENT_FMRI= x11/library/libdmx
COMPONENT_CLASSIFICATION = System/X11
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:253f90005d134fa7a209fbcbc5a3024335367c930adf0f3203e754cf32747243
COMPONENT_ARCHIVE_URL=  $(XORG_LIB_BASE_URL)/$(COMPONENT_ARCHIVE) 
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=      --disable-static

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += x11/header/dmxproto
REQUIRED_PACKAGES += x11/header/xextproto
REQUIRED_PACKAGES += x11/header/sun-ext-protos

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
