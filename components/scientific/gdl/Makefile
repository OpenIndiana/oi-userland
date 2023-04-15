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
# Copyright (c) 2017 Dariusz Sendkowski
# Copyright (c) 2023 Andreas Wacknitz
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        gdl
COMPONENT_VERSION=      1.0.2
COMPONENT_REVISION=     2
COMPONENT_PROJECT_URL=  https://gnudatalanguage.github.io/
COMPONENT_SUMMARY=      A free/libre/open source incremental compiler compatible with IDL and to some extent with PV-WAVE.	
COMPONENT_SRC=	        $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:9c623daef20a87fc9fb2ecc29587b38c3444b2706fa8bfe8694e4da4a094f76c
COMPONENT_ARCHIVE_URL=  https://github.com/gnudatalanguage/gdl/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         scientific/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/Suites
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -D_XOPEN_SOURCE=600

LDFLAGS += -lsocket -lnsl

CMAKE_OPTIONS += -DHDF=OFF
CMAKE_OPTIONS += -DHDF5DIR=/usr/include/hdf5
CMAKE_OPTIONS += -DPYTHON=OFF
CMAKE_OPTIONS += -DPSLIB=OFF
CMAKE_OPTIONS += -DGEOTIFF=OFF
CMAKE_OPTIONS += -DUDUNITS2=OFF
CMAKE_OPTIONS += -DGRIB=OFF
CMAKE_OPTIONS += -DGLPK=OFF
CMAKE_OPTIONS += -DSHAPELIB=OFF

COMPONENT_TEST_TRANSFORMS += \
	' -e "s/[0-9]*\.[0-9]* sec//" ' \
	' -n ' \
	' -e "/Passed/p" ' \
	' -e "/Failed/p" ' \
	' -e "/Skipped/p" ' \
	' -e "/Exception/p" ' \
	' -e "/passed/p" '

# Build dependencies
REQUIRED_PACKAGES += library/eigen3
REQUIRED_PACKAGES += library/qhull

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/gsl
REQUIRED_PACKAGES += image/graphicsmagick
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/plplot
REQUIRED_PACKAGES += library/c++/hdf5
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += library/netcdf-c
REQUIRED_PACKAGES += library/proj
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
