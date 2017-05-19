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

COMPONENT_NAME= jasper
COMPONENT_VERSION= 1.900.1
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= A free software-based reference implementation of the JPEG-2000 Part-1 CODEC
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:6b905a9c2aca2e275544212666eefc4eb44d95d0a57e4305457b407fe63f9494
COMPONENT_ARCHIVE_URL= \
  http://www.ece.uvic.ca/~frodo/jasper/software/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.ece.uvic.ca/~frodo/jasper/
COMPONENT_FMRI = codec/jasper
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_LICENSE = BSD-like
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# build with the distribution preferred libjpeg implementation
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --without-docs

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += image/library/$(JPEG_IMPLEM)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
