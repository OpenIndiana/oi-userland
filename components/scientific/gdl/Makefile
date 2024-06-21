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
# Copyright (c) 2023 Niklas Poslovski
# Copyright (c) 2024 Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        gdl
COMPONENT_VERSION=      1.0.6
COMPONENT_SUMMARY=      A free/libre/open source incremental compiler compatible with IDL and to some extent with PV-WAVE.
COMPONENT_PROJECT_URL=  https://gnudatalanguage.github.io/
COMPONENT_SRC=	        $(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:b02a257d59ad608cd300471e9cac6c23b6dc75938f79eaba812e30c56aed4865
COMPONENT_ARCHIVE_URL=  https://github.com/gnudatalanguage/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         scientific/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/Suites
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)

LDFLAGS += -lsocket -lnsl

CMAKE_OPTIONS += -DHDF=OFF
CMAKE_OPTIONS += -DHDF5DIR=$(USRINCLUDEDIR)/hdf5
CMAKE_OPTIONS += -DPYTHON=OFF
CMAKE_OPTIONS += -DPSLIB=OFF
CMAKE_OPTIONS += -DGEOTIFF=OFF
CMAKE_OPTIONS += -DUDUNITS2=OFF
CMAKE_OPTIONS += -DGRIB=OFF
CMAKE_OPTIONS += -DGLPK=OFF
CMAKE_OPTIONS += -DSHAPELIB=OFF

# Manually added build dependencies
REQUIRED_PACKAGES += library/eigen3
REQUIRED_PACKAGES += library/qhull

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
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
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
