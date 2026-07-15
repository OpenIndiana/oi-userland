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
# Copyright 2016 Aurelien Larcher
#

X11_CATEGORY= LIB
BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=			libxkbcommon
COMPONENT_VERSION=		1.13.2
COMPONENT_SUMMARY=		library to handle keyboard descriptions
COMPONENT_PROJECT_URL=	https://xkbcommon.org/
COMPONENT_SRC=			$(COMPONENT_NAME)-xkbcommon-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		xkbcommon-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:acc4d5f7c3cbba5f9f8d08d8bdbeede84ecede46792f47929aa9321873385528
COMPONENT_ARCHIVE_URL=	https://github.com/xkbcommon/libxkbcommon/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			x11/library/libxkbcommon
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

PYTHON_VERSION= 3.14
COMPONENT_PRE_TEST_ACTION += $(GSED) -i -e 's?env python3?python$(PYTHON_VERSION)?' $(SOURCE_DIR)/test/*.py ;

CONFIGURE_OPTIONS += -Denable-wayland=false
CONFIGURE_OPTIONS += -Denable-docs=true

CONFIGURE_ENV += $(COMPONENT_BUILD_ENV)

COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32) ;

# Note that one of the tests fails with a type error; probably because our python-3.9 is too old.
#     rules: str | None = None
#	TypeError: unsupported operand type(s) for |: 'type' and 'NoneType'
COMPONENT_TEST_ENV += HOME=/tmp

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxml2/32
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
