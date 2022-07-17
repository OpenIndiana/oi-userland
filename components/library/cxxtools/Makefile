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
# Copyright 2016 Jim Klimov
#

BUILD_STYLE=configure
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cxxtools
COMPONENT_VERSION=      2.2.1
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=      Cxxtools is a comprehensive C++ class library for Unix and Linux
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:8cebb6d6cda7c93cc4f7c0d552a68d50dd5530b699cf87916bb3b708fdc4e342
COMPONENT_ARCHIVE_URL=  \
	http://www.tntnet.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.tntnet.org/cxxtools.html
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE
CFLAGS.32=-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE

CXXFLAGS+=$(CXXFLAGS.$(BITS))
CFLAGS+=$(CFLAGS.$(BITS))

CONFIGURE_OPTIONS+= --sysconfdir=/etc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
