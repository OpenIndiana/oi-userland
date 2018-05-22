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
COMPONENT_VERSION=      5.13.0
COMPONENT_PROJECT_URL=	http://plplot.sourceforge.net
COMPONENT_SUMMARY=	A cross-platform software package for creating scientific plots.
COMPONENT_FMRI=         image/plplot
COMPONENT_CLASSIFICATION=Applications/Graphics and Imaging
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ec36bbee8b03d9d1c98f8fd88f7dc3415560e559b53eb1aa991c2dcf61b25d2b
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)%20Source/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_BINDIR.64= $(CMAKE_BINDIR.32)


CMAKE_OPTIONS.64 += -DwxWidgets_CONFIG_EXECUTABLE=/usr/bin/$(MACH64)/wx-config
CMAKE_OPTIONS += -DENABLE_ada=OFF
CMAKE_OPTIONS += -DENABLE_cxx=ON
CMAKE_OPTIONS += -DENABLE_d=ON
CMAKE_OPTIONS += -DENABLE_fortran=ON
CMAKE_OPTIONS += -DENABLE_java=ON
CMAKE_OPTIONS += -DENABLE_lua=ON
CMAKE_OPTIONS += -DENABLE_ocaml=OFF
CMAKE_OPTIONS += -DENABLE_octave=OFF
CMAKE_OPTIONS += -DENABLE_pdl=OFF
CMAKE_OPTIONS += -DENABLE_python=OFF
CMAKE_OPTIONS += -DENABLE_qt=ON
CMAKE_OPTIONS += -DENABLE_pyqt4=OFF
CMAKE_OPTIONS += -DENABLE_tcl=ON
CMAKE_OPTIONS += -DENABLE_itcl=OFF
CMAKE_OPTIONS += -DENABLE_tk=ON
CMAKE_OPTIONS += -DENABLE_itk=OFF
CMAKE_OPTIONS += -DENABLE_wxwidgets=ON

CMAKE_OPTIONS += -DENABLE_tk=OFF
CMAKE_OPTIONS += -DENABLE_tk=OFF
CMAKE_OPTIONS += -DDEFAULT_NO_QT_DEVICES=ON
CMAKE_OPTIONS += -DUSE_RPATH=OFF
CMAKE_OPTIONS += -DBUILD_TEST=ON

COMPONENT_TEST_CMD = ctest


COMPONENT_BUILD_ARGS = 

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/qhull
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/gfortran-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
