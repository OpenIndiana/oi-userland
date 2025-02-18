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

COMPONENT_NAME= schroedinger
COMPONENT_VERSION= 1.0.11
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= Library for decoding and encoding video in the Dirac format
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:1e572a0735b92aca5746c4528f9bebd35aa0ccf8619b22fa2756137a8cc9f912
COMPONENT_ARCHIVE_URL= https://launchpad.net/schroedinger/trunk/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://launchpad.net/schroedinger
COMPONENT_FMRI= library/video/libschroedinger
COMPONENT_CLASSIFICATION= System/Media
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING.LGPL

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += library/orc
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
