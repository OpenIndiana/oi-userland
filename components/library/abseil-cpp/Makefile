#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD = yes
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         abseil-cpp
COMPONENT_VERSION=	20240116.3
COMPONENT_SUMMARY=      Collection of C++ library code designed to augment the C++ standard library
COMPONENT_PROJECT_URL=  https://abseil.io
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e887b423da5a1ba66e71610094fd7147ff2febfedccdfbf00f2c644ac21adf83
COMPONENT_ARCHIVE_URL=	https://github.com/abseil/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/c++/abseil-cpp
COMPONENT_CLASSIFICATION=       Development/C++
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE= LICENSE

COMPONENT_FMRI.library=		$(COMPONENT_FMRI)-$(SOVER)
COMPONENT_SUMMARY.library=	$(COMPONENT_SUMMARY) (runtime libraries)

include $(WS_MAKE_RULES)/common.mk

# We need shared libraries, not static
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
# Build tests
CMAKE_OPTIONS += -DABSL_BUILD_TESTING=ON
# ... and use our packaged googletest
CMAKE_OPTIONS += -DABSL_USE_EXTERNAL_GOOGLETEST=ON

# Dynamic library version number
SOVER := $(shell echo $(COMPONENT_VERSION) | $(CUT) -c 3-6)

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/googletest
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
