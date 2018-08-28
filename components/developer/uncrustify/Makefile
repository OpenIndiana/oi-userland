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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         uncrustify
COMPONENT_VERSION=      0.67
COMPONENT_SUMMARY=      source code beautifier
COMPONENT_PROJECT_URL=  http://uncrustify.sourceforge.net/
COMPONENT_FMRI=         developer/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=   Development/Source Code Management
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
    sha256:54f15c8ebddef120522db21f38fac1dd3b0a285fbf60a8b71f9e333e96cf6ddc
COMPONENT_LICENSE=  GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

UNPACK_ARGS+=-r $(COMPONENT_SRC)

COMPONENT_POST_INSTALL_ACTION= $(MKDIR) -p $(PROTO_DIR)/usr/share/doc/uncrustify && \
    $(CP) -r $(SOURCE_DIR)/documentation/htdocs $(PROTO_DIR)/usr/share/doc/uncrustify

COMPONENT_TEST_ENV += CC=$(CC)
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
    '-ne "/tests passed,/p" '

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
