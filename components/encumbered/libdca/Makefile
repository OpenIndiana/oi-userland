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

COMPONENT_NAME= libdca
COMPONENT_VERSION= 0.0.5
COMPONENT_FMRI = library/audio/libdca
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= A free library for decoding DTS Coherent Acoustics streams
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:dba022e022109a5bacbe122d50917769ff27b64a7bba104bd38ced8de8510642
COMPONENT_ARCHIVE_URL= \
  http://download.videolan.org/pub/videolan/libdca/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.videolan.org/developers/libdca.html
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CFLAGS += $($(COMPILER)_PIC)

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
