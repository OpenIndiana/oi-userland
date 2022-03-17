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
# Copyright 2022, Daniel Chan
#

BUILD_BITS=		64
BUILD_STYLE=	justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		FreeImage
COMPONENT_VERSION_MAJOR=3
COMPONENT_VERSION_MINOR=18
COMPONENT_VERSION_PATCH=0
COMPONENT_VERSION=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR).$(COMPONENT_VERSION_PATCH)
COMPONENT_SUMMARY=	A library project for developers to support popular graphics image formats
COMPONENT_PROJECT_URL=	https://freeimage.sourceforge.io
COMPONENT_FMRI=		library/libfreeimage
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)$(COMPONENT_VERSION_MAJOR)$(COMPONENT_VERSION_MINOR)$(COMPONENT_VERSION_PATCH).zip
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/freeimage/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:f41379682f9ada94ea7b34fe86bf9ee00935a3147be41b6569c9605a53e438fd
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	license-gplv3.txt

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION=cp $(SOURCE_DIR)/../libfreeimage.pc $(SOURCE_DIR)/
COMPONENT_BUILD_GMAKE_ARGS="file=Makefile.gnu"
CFLAGS+=-fPIC
CFLAGS+=-fexceptions
CFLAGS+=-fvisibility=hidden
CXXFLAGS+=-fPIC 
CXXFLAGS+=-fexceptions
CXXFLAGS+=-fvisibility=hidden 
CXXFLAGS+=-Wno-ctor-dtor-privacy

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
