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
# Copyright 2018 Jason Martin
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE=cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         uncrustify
COMPONENT_VERSION=      0.77.1
#COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      source code beautifier
COMPONENT_PROJECT_URL=  https://uncrustify.sourceforge.net/
COMPONENT_FMRI=         developer/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/Source Code Management
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/$(COMPONENT_NAME)/files/uncrustify-077.1/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH= \
	sha256:939d50c8206a5e016a09947d51bb64b8a4275d89181efc484f44d5e5c3e66666
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_POST_INSTALL_ACTION= $(MKDIR) -p $(PROTO_DIR)/usr/share/doc/uncrustify && \
    $(CP) -r $(SOURCE_DIR)/documentation/htdocs $(PROTO_DIR)/usr/share/doc/uncrustify

COMPONENT_TEST_ENV += CC=$(CC)
COMPONENT_TEST_TRANSFORMS += \
    '-ne "/tests passed,/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
