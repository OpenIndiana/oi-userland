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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        gdl
COMPONENT_VERSION=      0.9.7
COMPONENT_REVISION=     3
COMPONENT_PROJECT_URL=  http://gnudatalanguage.sourceforge.net/	
COMPONENT_SUMMARY=      A free/libre/open source incremental compiler compatible with IDL and to some extent with PV-WAVE.	
COMPONENT_FMRI=         scientific/gdl
COMPONENT_CLASSIFICATION=Development/Suites
COMPONENT_SRC=	        $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:2b5945d06e4d95f01cb70a3c432ac2fa4c81e1b3ac7c02687a6704ab042a7e21
COMPONENT_ARCHIVE_URL=  http://downloads.sourceforge.net/project/gnudatalanguage/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

LD_Z_IGNORE=

CMAKE_OPTIONS += -DHDF=OFF
CMAKE_OPTIONS += -DHDF5DIR=/usr/include/hdf5
CMAKE_OPTIONS += -DPYTHON=OFF
CMAKE_OPTIONS += -DPSLIB=OFF
CMAKE_OPTIONS += -DWXWIDGETSDIR=/usr/bin/amd64


CONFIGURE_BINDIR.64=	$(CONFIGURE_BINDIR.32)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Build dependencies
REQUIRED_PACKAGES += library/eigen3

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/gsl
REQUIRED_PACKAGES += image/graphicsmagick
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/plplot
REQUIRED_PACKAGES += library/c++/hdf5
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/graphics/wxwidgets
REQUIRED_PACKAGES += library/mpich/gcc
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/netcdf
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
