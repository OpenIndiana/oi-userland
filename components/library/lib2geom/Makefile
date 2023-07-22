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
# Copyright 2023 Andreas Wacknitz
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lib2geom
COMPONENT_VERSION=	1.2.2
COMPONENT_SUMMARY=	easy 2D graphics library
COMPONENT_PROJECT_URL=	https://gitlab.com/inkscape/lib2geom
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:1c22a7be571d2e2f3ee98424614ffd6a42fe73dedbd2ccfb0967ecb02f77edeb
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	LGPLv2.1, MPL-1.1

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -D2GEOM_BUILD_SHARED:BOOL=ON

#unexport SHELLOPTS
# We have one failing test:
# nl-vector-test: fatal: relocation error: file /usr/lib/64/libgsl.so.27: symbol cblas_dcopy: referenced symbol not found
# This probably happens because cblas_dcopy is in libgslcblas
COMPONENT_TEST_TRANSFORMS += \
	' -e "s/[0-9]*\.[0-9]* sec//" ' \
	' -n ' \
	' -e "/passed/p" ' \
	' -e "/Passed/p" ' \
	' -e "/PASSED/p" ' \
	' -e "/FAILED/p" ' \
	' -e "/Subprocess killed/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/gsl
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/double-conversion
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
