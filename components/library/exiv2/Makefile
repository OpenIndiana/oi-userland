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
# Copyright 2017 Carsten Grzemba
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= exiv2
COMPONENT_VERSION= 0.28.5
COMPONENT_SUMMARY= Image metadata library and tools
COMPONENT_PROJECT_URL= https://www.exiv2.org
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e1671f744e379a87ba0c984617406fdf8c0ad0c594e5122f525b2fb7c28d394d
COMPONENT_ARCHIVE_URL= https://github.com/Exiv2/exiv2/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI= image/library/exiv2
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS  += $(XPG6MODE)
LDFLAGS += -lnsl -lsocket

# Manually added build dependencies
TEST_REQUIRED_PACKAGES += developer/googletest

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/inih
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
