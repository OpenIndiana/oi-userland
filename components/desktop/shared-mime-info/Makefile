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

COMPONENT_NAME= shared-mime-info

COMPONENT_VERSION= 0.90
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= application/MIME type registry
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:52c9f84a8c72de631a0458542980b1728560f59845eb5e93e1dbe825f4b72304
COMPONENT_ARCHIVE_URL= \
  http://freedesktop.org/~hadess/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.freedesktop.org/Software/shared-mime-info
COMPONENT_FMRI = desktop/shared-mime-info
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_LICENSE = GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_ENV+= PERL=$(PERL)

COMPONENT_BUILD_ARGS=

COMPONENT_INSTALL_TARGET =  install-strip

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
