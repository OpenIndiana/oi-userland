#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Artem Shepelev. All rights reserved.
#
BUILD_BITS=32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         arj
COMPONENT_VERSION=      3.10.22
COMPONENT_REVISION=     1
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SUMMARY=	Arj archiver utility
COMPONENT_PROJECT_URL=  http://arj.sourceforge.net/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:589e4c9bccc8669e7b6d8d6fcd64e01f6a2c21fe10aad56a83304ecc3b96a7db
COMPONENT_ARCHIVE_URL=  http://arj.sourceforge.net/files/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = (cp -r $(SOURCE_DIR)/* $(BUILD_DIR_$(BITS))/) 

COMPONENT_PREP_ACTION =	(cd $(SOURCE_DIR)/gnu && \
					autoconf)
CONFIGURE_SCRIPT = $(SOURCE_DIR)/gnu/configure

COMPONENT_BUILD_ARGS=
COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
