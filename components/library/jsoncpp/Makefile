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
# Copyright 2022 erwinlem
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		jsoncpp
COMPONENT_VERSION=	1.9.5
COMPONENT_REVISION= 2
COMPONENT_SUMMARY=	A C++ library for interacting with JSON.
COMPONENT_PROJECT_URL=	https://github.com/open-source-parsers/jsoncpp
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f409856e5920c18d0c2fb85276e24ee607d2a09b5e7d5f0a371368903c275da2
COMPONENT_FMRI=		library/${COMPONENT_NAME}
COMPONENT_CLASSIFICATION=Development/C++
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
