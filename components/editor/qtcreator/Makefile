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
# Copyright 2022 Stephan Althaus
# Copyright 2022 Daniel Chan
#

BUILD_BITS  =	64
BUILD_STYLE = cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				qtcreator
COMPONENT_VERSION_MAJOR=	7.0
COMPONENT_VERSION_MINOR=	1
COMPONENT_VERSION=			$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
COMPONENT_REVISION=			1
COMPONENT_SUMMARY=			QT Creator - A Cross-platform IDE for Application Development
COMPONENT_PROJECT_URL=		https://www.qt.io/product/development-tools
COMPONENT_SRC=				qt-creator-opensource-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=			$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=		sha256:da78f293829851e32f6bf25540791697606809e47a32ca8439561fcbab96b22e
COMPONENT_ARCHIVE_URL=		https://download.qt.io/official_releases/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=				editor/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=      	GPLv3

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=/usr/lib/qt/5.15/bin/amd64:$(PATH.gnu)
CXXFLAGS += -fPIC
CXXFLAGS += -I/usr/gcc/$(GCC_VERSION)/include/c++/$(GCC_VERSION)
LDFLAGS += -lxnet
LDFLAGS += -Wl,-rpath,/usr/lib/qt/5.15/lib/amd64:/usr/clang/13.0/lib:/usr/lib/amd64/qtcreator:/usr/lib/amd64/qtcreator/plugins

Qt5_DIR  ="/usr/lib/qt/5.15/lib/amd64/cmake/Qt5"
Clang_DIR="/usr/clang/13.0/lib/cmake/clang"
LLVM_INSTALL_DIR="/usr/clang/13.0"
INSTALL_ROOT=$(PROTO_DIR)/usr

# Set path to Qt5 libs
QT5_LIBDIR = /usr/lib/qt/5.15/lib/amd64
GCC_LIBDIR = /usr/gcc/$(GCC_VERSION)/lib/amd64
QTC_LIBDIR = /usr/lib/amd64/qtcreator
QTC_LIBDIR_2 = /usr/lib/amd64/qtcreator/plugins
CLANG_LIBDIR = /usr/clang/13.0/lib
STD_LIBDIR = /usr/lib/amd64

COMPONENT_INSTALL_ENV+= INSTALL_ROOT=$(PROTO_DIR)/usr

COMPONENT_PRE_CMAKE_ACTION += cp -r $(SOURCE_DIR)/* $(@D)/
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCMAKE_PREFIX_PATH="$(QT5_LIBDIR)/cmake;/usr/clang/13.0"
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=/usr
CMAKE_OPTIONS += -DPython3_EXECUTABLE=/usr/bin/python3.9
CMAKE_OPTIONS += -DWITH_DOCS=ON
CMAKE_OPTIONS += -DBUILD_DEVELOPER_DOCS=ON
CMAKE_OPTIONS += -DBUILD_QBS=OFF
CMAKE_OPTIONS += -DQTC_CLANG_BUILDMODE_MATCH=ON

COMPONENT_POST_INSTALL_ACTION = \
	chmod +x $(PROTO_DIR)/usr/bin/*; \
	chmod +x $(PROTO_DIR)/usr/libexec/*


$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CMAKE_ACTION)
	(cd $(@D) ; $(ENV) $(CMAKE_ENV) \
		$(CMAKE) $(CMAKE_OPTIONS) $(@D))
	$(COMPONENT_POST_CMAKE_ACTION)
	$(TOUCH) $@

# Build dependencies
REQUIRED_PACKAGES += developer/clang-13

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += runtime/clang-13
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
