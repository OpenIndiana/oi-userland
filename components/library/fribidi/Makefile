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

COMPONENT_NAME= fribidi
COMPONENT_VERSION= 0.19.7
COMPONENT_FMRI= library/fribidi
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SUMMARY= Free Implementation of the Unicode Bidirectional Algorithm
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:08222a6212bbc2276a2d55c3bf370109ae4a35b689acbc66571ad2a670595a8e
COMPONENT_ARCHIVE_URL= \
  http://fribidi.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://fribidi.org/
COMPONENT_LICENSE= LGPLv2.1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
