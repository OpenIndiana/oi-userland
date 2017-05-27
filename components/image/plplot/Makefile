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

COMPONENT_NAME=         plplot
COMPONENT_VERSION=      5.9.9
COMPONENT_PROJECT_URL=	http://plplot.sourceforge.net
COMPONENT_SUMMARY=	A cross-platform software package for creating scientific plots.
COMPONENT_FMRI=         image/plplot
COMPONENT_CLASSIFICATION=Applications/Graphics and Imaging
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:747e5a043681f3e20df30d159f6e8517cb1e25e502322adcd80e8ca53ec2c90d
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)%20Source/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_BINDIR.64= $(CMAKE_BINDIR.32)


CMAKE_OPTIONS.64 += -DwxWidgets_CONFIG_EXECUTABLE=/usr/bin/$(MACH64)/wx-config
CMAKE_OPTIONS += -DENABLE_d=OFF
CMAKE_OPTIONS += -DENABLE_ada=OFF
CMAKE_OPTIONS += -DDEFAULT_NO_QT_DEVICES=ON
CMAKE_OPTIONS += -DUSE_RPATH=OFF
CMAKE_OPTIONS += -DBUILD_TEST=ON

COMPONENT_TEST_CMD = ctest


COMPONENT_BUILD_ARGS = 

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/wxwidgets
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/gfortran-4-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
