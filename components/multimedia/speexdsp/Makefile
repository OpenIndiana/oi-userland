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

COMPONENT_NAME= speexdsp
COMPONENT_VERSION= 1.2rc3
IPS_COMPONENT_VERSION= 1.2.0.3
COMPONENT_SUMMARY= Speex DSP library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:4ae688600039f5d224bdf2e222d2fbde65608447e4c2f681585e4dca6df692f1
COMPONENT_ARCHIVE_URL= \
  http://downloads.xiph.org/releases/speex/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.speex.org/
COMPONENT_FMRI=	library/speexdsp
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE = BSD
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
