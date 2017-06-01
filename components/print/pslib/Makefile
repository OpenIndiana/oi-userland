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
# Copyright 2017 Dariusz Sendkowski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         pslib
COMPONENT_VERSION=      0.4.5
COMPONENT_SUMMARY=      C-library to create PostScript files on the fly. 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7a33928982b281660206bb3749a4a563e3ac987eea64f41696f212df345212be
COMPONENT_ARCHIVE_URL=  http://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://pslib.sourceforge.net/
COMPONENT_FMRI=         print/pslib
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk


PATH=$(PATH.gnu)

CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --disable-static


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TEST)

REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += system/library
