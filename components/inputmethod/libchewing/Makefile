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

COMPONENT_NAME=           libchewing
COMPONENT_VERSION=        0.9.1
COMPONENT_SUMMARY=        libchewing - The intelligent phonetic input method library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.zst
COMPONENT_ARCHIVE_HASH=   sha256:e98b76c306552148b7d85f0e596860751d9eef4bc8f2dfc053177b14f421c31f
COMPONENT_ARCHIVE_URL=    https://github.com/chewing/libchewing/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/library/libchewing
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        LGPLv2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/chewing/libchewing

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

PATH= $(PATH.gnu)

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

#To prevent git describe --dirty
COMPONENT_PREP_ACTION= ( sed -i 's/find_package(Git)/\#find_package(Git)/g'  $(SOURCE_DIR)/CMakeLists.txt) ;

# Manually added build dependencies
REQUIRED_PACKAGES += developer/lang/rustc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
