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
# Copyright 2018 Jason Martin
#

BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mpdecimal
COMPONENT_VERSION= 4.0.0
COMPONENT_SUMMARY= Complete implementation of the General Decimal Arithmetic Specification
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:942445c3245b22730fd41a67a7c5c231d11cb1b9936b9c0f76334fb7d0b4468c
COMPONENT_ARCHIVE_URL= https://www.bytereef.org/software/mpdecimal/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.bytereef.org/mpdecimal/
COMPONENT_FMRI= library/math/libmpdec2
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= COPYRIGHT.txt

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --enable-static=false
CONFIGURE_OPTIONS += --enable-doc=false

COMPONENT_TEST_TRANSFORMS += '-e "/PASS/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
