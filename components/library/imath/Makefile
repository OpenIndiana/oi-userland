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
# Copyright 2022 Daniel Chan
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Imath
COMPONENT_VERSION=	3.1.12
COMPONENT_SUMMARY=	C++ representation of 2D and 3D vectors
COMPONENT_PROJECT_URL=	https://github.com/AcademySoftwareFoundation/$(COMPONENT_NAME)
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8a1bc258f3149b5729c2f4f8ffd337c0e57f09096e4ba9784329f40c4a9035da
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=			library/imath
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=		BSD 3-Clause
COMPONENT_LICENSE_FILE=	LICENSE.md

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(USRDIR)
CMAKE_OPTIONS.64 += -DCMAKE_INSTALL_LIBDIR=lib/$(MACH64)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
