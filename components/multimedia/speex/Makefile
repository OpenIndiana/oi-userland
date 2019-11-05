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

COMPONENT_NAME= speex
COMPONENT_VERSION= 1.2rc2
IPS_COMPONENT_VERSION= 1.2.0.2
COMPONENT_SUMMARY= Open Source speech codec
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:caa27c7247ff15c8521c2ae0ea21987c9e9710a8f2d3448e8b79da9806bce891
COMPONENT_ARCHIVE_URL= \
  http://downloads.xiph.org/releases/speex/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.speex.org/
COMPONENT_FMRI=	codec/speex
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
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
