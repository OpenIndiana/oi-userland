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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= soundtouch
COMPONENT_VERSION= 1.9.2
COMPONENT_SUMMARY= Audio Processing Library
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:4aa443594d77986bf977c2856f5530a8015db406631e4b996f962b1e6809883e
COMPONENT_ARCHIVE_URL= \
  http://www.surina.net/soundtouch/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.surina.net/soundtouch
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING.TXT
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = library/audio/soundtouch

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					$(CONFIG_SHELL) bootstrap )

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-x86-optimizations

CONFIGURE_ENV += AM_CXXFLAGS="$(CXXFLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
