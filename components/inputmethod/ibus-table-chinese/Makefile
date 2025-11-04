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
# Copyright 2025 Jiwon Na
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           ibus-table-chinese
COMPONENT_VERSION=        1.8.14
COMPONENT_SUMMARY=        ibus-table-chinese - Chinese tables for IBus-Table
COMPONENT_PROJECT_URL=    https://github.com/mike-fabian/ibus-table-chinese
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:6c2b0071d2d24494476e80c52a0d7979efac739797f63ffeaf5338254fb92572
COMPONENT_ARCHIVE_URL=    https://github.com/mike-fabian/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/ibus/table/chinese
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        GPLv3
COMPONENT_LICENSE_FILE=   COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CMAKE_OPTIONS += -DCMAKE_POLICY_VERSION_MINIMUM=3.5

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/input-method/ibus/table

# Auto-generated dependencies
