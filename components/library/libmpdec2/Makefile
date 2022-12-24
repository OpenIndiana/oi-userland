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

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mpdecimal
COMPONENT_VERSION= 2.4.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Complete implementation of the General Decimal Arithmetic Specification
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:83c628b90f009470981cf084c5418329c88b19835d8af3691b930afccb7d79c7
COMPONENT_ARCHIVE_URL= https://www.bytereef.org/software/mpdecimal/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.bytereef.org/mpdecimal/
COMPONENT_FMRI= library/math/libmpdec2
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_POST_UNPACK_ACTION= ( \
    $(MV) $(SOURCE_DIR)/examples/ $(SOURCE_DIR)/doc/ )

COMPONENT_PRE_CONFIGURE_ACTION= ( cp -a $(SOURCE_DIR)/* $(@D) )

COMPONENT_TEST_TRANSFORMS += '-e "/PASS/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
