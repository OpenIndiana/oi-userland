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

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         plplot
COMPONENT_VERSION=      5.15.0
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=		A cross-platform software package for creating scientific plots.
COMPONENT_PROJECT_URL=	https://plplot.sourceforge.net
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:b92de4d8f626a9b20c84fc94f4f6a9976edd76e33fb1eae44f6804bdcc628c7b
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)%20Source/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=         image/plplot
COMPONENT_CLASSIFICATION=Applications/Graphics and Imaging
COMPONENT_LICENSE=		LGPLv2
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS= 

CMAKE_OPTIONS += -DwxWidgets_CONFIG_EXECUTABLE=/usr/bin/wx-config
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
CMAKE_OPTIONS += -DJAVA_INCLUDE_PATH=/usr/jdk/latest/include
CMAKE_OPTIONS += -DJAVA_AWT_LIBRARY=/usr/java/jre/lib/amd64/libjawt.so
CMAKE_OPTIONS += -DJAVA_JVM_LIBRARY=/usr/java/jre/lib/amd64/server/libjvm.so
CMAKE_OPTIONS += -DENABLE_tk=OFF
CMAKE_OPTIONS += -DDEFAULT_NO_QT_DEVICES=ON
CMAKE_OPTIONS += -DUSE_RPATH=OFF
CMAKE_OPTIONS += -DBUILD_TEST=ON

COMPONENT_TEST_CMD = ctest
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*\.[0-9]* sec//" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GFORTRAN_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
