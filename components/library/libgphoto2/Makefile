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

COMPONENT_NAME= libgphoto2
COMPONENT_VERSION= 2.5.18
COMPONENT_REVISION=1
COMPONENT_SUMMARY= Digital camera library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:5b17b89d7ca0ec35c72c94ac3701e87d49e52371f9509b8e5c08c913ae57a7ec
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/gphoto/files/libgphoto/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://www.gphoto.org
COMPONENT_FMRI = library/libgphoto2-2
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# build with the distribution preferred libjpeg implementation
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

# Without this we get issues with unresolved references to  __deregister_frame_info_bases
LD_B_DIRECT=
LD_Z_IGNORE=

CFLAGS.32 += -D_FILE_OFFSET_BITS=64
CFLAGS	  += $(CFLAGS.$(BITS))
CFLAGS	  += -std=gnu99 $(CPP_XPG6MODE)

COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

CONFIGURE_OPTIONS+= --with-doc-dir=/usr/share/doc/libgphoto2
CONFIGURE_OPTIONS+= --disable-static

ENV = /usr/bin/env -i

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
