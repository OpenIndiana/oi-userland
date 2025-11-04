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
# Copyright 2022 Benjamin S. Osenbach
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= sxhkd
COMPONENT_VERSION= 0.6.3
COMPONENT_SUMMARY= Simple X hotkey daemon
COMPONENT_PROJECT_URL= https://github.com/baskerville/sxhkd
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/baskerville/sxhkd/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:9d7a64d73f7114a24ff93a35a2662afd9807e0df9ffbfabd24230b4872503fcb
COMPONENT_FMRI= application/sxhkd
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += -Wno-error=implicit-function-declaration

COMPONENT_BUILD_ENV += PREFIX=/usr

COMPONENT_INSTALL_ENV += PREFIX=/usr

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
