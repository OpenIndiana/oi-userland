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
# Copyright 2023 Klaus Ziegler
#

BUILD_BITS= 64_and_32
USE_COMMON_TEST_MASTER= yes
USE_DEFAULT_TEST_TRANSFORMS= yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libdatrie
COMPONENT_VERSION_MAJOR=	0
COMPONENT_VERSION_MINOR=	2
COMPONENT_VERSION_MICRO=	13
COMPONENT_VERSION_DL=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
COMPONENT_VERSION=      $(COMPONENT_VERSION_DL).$(COMPONENT_VERSION_MICRO)
COMPONENT_SUMMARY=      $(COMPONENT_NAME) - A double-array trie library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:12231bb2be2581a7f0fb9904092d24b0ed2a271a16835071ed97bed65267f4be
COMPONENT_ARCHIVE_URL=  https://github.com/tlwg/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://github.com/tlwg/libdatrie
COMPONENT_FMRI=         system/input-method/library/libdatrie
COMPONENT_CLASSIFICATION=System/Localizations
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

#COMPONENT_TEST_TRANSFORMER = $(NAWK)
#COMPONENT_TEST_TRANSFORMS = "'/^(PASS|^#)/'"

# For test suites to pass
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
