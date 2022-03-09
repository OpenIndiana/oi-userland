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
#

BUILD_BITS  =	64
BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         qtcreator
COMPONENT_VERSION_MAJOR =      4
COMPONENT_VERSION_MINOR =      11
COMPONENT_VERSION_SUB   =      2
COMPONENT_VERSION       = $(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR).$(COMPONENT_VERSION_SUB)
COMPONENT_FMRI=         editor/qtcreator
COMPONENT_CLASSIFICATION=   Applications/Accessories
COMPONENT_PROJECT_URL=  https://www.qt.io/product/development-tools
COMPONENT_SUMMARY=      QT Creator - A Cross-platform IDE for Application Development
COMPONENT_SRC=          qt-creator-opensource-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=  https://download.qt.io/archive/qtcreator/$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
#COMPONENT_ARCHIVE_URL=  https://duedinghausen.eu/tarballs/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:8d67e45b66944fdb0f879cbfae341af7e38d6a348cf18332b5cb9f07937aae02
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= qtcreator.licence

IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION)

Qt5_DIR  ="/usr/lib/qt/5.12/lib/amd64/cmake/Qt5"
Clang_DIR="/usr/clang/13.0/lib/cmake/clang"
LLVM_INSTALL_DIR="/usr/clang/13.0"
#PREFIX="/usr"
#QT_PREFIX="/usr"
INSTALL_ROOT=$(PROTO_DIR)/usr

# Set path to Qt5 libs
QT5_LIBDIR = /usr/lib/qt/5.12/lib/amd64
GCC_LIBDIR = /usr/gcc/7/lib/amd64
QTC_LIBDIR = /usr/lib/qtcreator
QTC_LIBDIR_2 = /usr/lib/qtcreator/plugins
CLANG_LIBDIR = /usr/clang/13.0/lib
STD_LIBDIR = /usr/lib/amd64

#CXXFLAGS += -fpermissive 
#CFLAGS += -fpermissive 
CMAKE_OPTIONS += "-DCMAKE_BUILD_TYPE=Release "
CMAKE_OPTIONS += "-G Ninja "
# Set path to Qt5 cmake modules.
CMAKE_OPTIONS += -DCMAKE_PREFIX_PATH="$(QT5_LIBDIR)/cmake;/usr/clang/13.0"
CMAKE_OPTIONS += -DPYTHON_EXECUTABLE=/usr/bin/python3.9
CMAKE_OPTIONS += -DQTC_DISABLE_CLANG_REFACTORING=1
#CMAKE_OPTIONS += -DBUILD_PLUGIN_CLANGPCHMANAGER=OFF

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

#COMPONENT_INSTALL_ACTION = $(shell PREFIX=$PROTO_DIR gmake install)
#COMPONENT_INSTALL_ARGS+= prefix=$(PROTO_DIR)
#COMPONENT_INSTALL_ARGS+= INSTALL_ROOT=$(PROTO_DIR)
#COMPONENT_BUILD_ENV+= PREFIX="/usr"
#COMPONENT_BUILD_ENV+= QT_PREFIX="/usr"
COMPONENT_INSTALL_ENV+= INSTALL_ROOT=$(PROTO_DIR)/usr
#COMPONENT_INSTALL_ENV+= PREFIX="/usr"
#COMPONENT_INSTALL_ENV+= QT_PREFIX="/usr"
#COMPONENT_INSTALL_ENV+= INSTALL_ROOT=$(BUILD_DIR)/usr

# Need this to prevent symlinks in the build area build/amd64
#COMPONENT_PRE_CONFIGURE_ACTION = ( cp -r $(SOURCE_DIR)/* $(@D) )
COMPONENT_PRE_CONFIGURE_ACTION=

# Need this to prevent symlinks in the build area build/amd64
#COMPONENT_PRE_CONFIGURE_ACTION = \
#    ( cp -r $(SOURCE_DIR)/* $(@D) )
#COMPONENT_PREP_ACTION += \
#	( mkdir $(SOURCE_DIR)/../build ; mkdir $(SOURCE_DIR)/../build/amd64 ; cp -ar $(SOURCE_DIR)/* $(SOURCE_DIR)/../build/amd64/ )

COMPONENT_PRE_BUILD_ACTION = \
		( rm -rf $(@D)/* ; cp -ar $(SOURCE_DIR)/* $(@D)/ ) ; \
        ( cd $(@D) && QTC_DISABLE_CLANG_REFACTORING=1 qmake QMAKE_LDFLAGS=" -lsocket " QT_PREFIX="/usr" PREFIX="/usr" LLVM_INSTALL_DIR="/usr/clang/13.0" -r 'CONFIG+=release')
#COMPONENT_BUILD_ARGS= -j1

#COMPONENT_POST_INSTALL_ACTION = \
#	for file in $(VBOX_QT5_LIBS); \
#	do \
#		/usr/bin/elfedit -e 'dyn:value -s RUNPATH "$(VBOX_QT5_RPATH)"' $(PROTO_DIR)$(VBOX_LIBDIR)/$$file; \
#		/usr/bin/elfedit -e 'dyn:value -s RPATH   "$(VBOX_QT5_RPATH)"' $(PROTO_DIR)$(VBOX_LIBDIR)/$$file; \
#	done; \

COMPONENT_POST_INSTALL_ACTION = ( \
 /usr/bin/find $(PROTO_DIR)$(USRLIBDIR) -name "*.so" -exec elfedit -e 'dyn:value -s RUNPATH "$(GCC_LIBDIR):$(QT5_LIBDIR):$(CLANG_LIBDIR):$(QTC_LIBDIR):$(QTC_LIBDIR_2)"' {} \; ; \
 /usr/bin/find $(PROTO_DIR)$(USRLIBDIR) -name "*.so" -exec elfedit -e 'dyn:value -s RPATH   "$(GCC_LIBDIR):$(QT5_LIBDIR):$(CLANG_LIBDIR):$(QTC_LIBDIR):$(QTC_LIBDIR_2)"' {} \; ; \
 /usr/bin/find $(PROTO_DIR)$(USRBINDIR) -name "*" -exec elfedit -e 'dyn:value -s RUNPATH "$(GCC_LIBDIR):$(QT5_LIBDIR):$(CLANG_LIBDIR):$(QTC_LIBDIR):$(QTC_LIBDIR_2)"' {} \; ; \
 /usr/bin/find $(PROTO_DIR)$(USRBINDIR) -name "*" -exec elfedit -e 'dyn:value -s RPATH   "$(GCC_LIBDIR):$(QT5_LIBDIR):$(CLANG_LIBDIR):$(QTC_LIBDIR):$(QTC_LIBDIR_2)"' {} \; ; \
 /usr/bin/find $(PROTO_DIR)/usr/libexec -name "*" -exec elfedit -e 'dyn:value -s RUNPATH "$(GCC_LIBDIR):$(QT5_LIBDIR):$(CLANG_LIBDIR):$(QTC_LIBDIR):$(QTC_LIBDIR_2)"' {} \; ; \
 /usr/bin/find $(PROTO_DIR)/usr/libexec -name "*" -exec elfedit -e 'dyn:value -s RPATH   "$(GCC_LIBDIR):$(QT5_LIBDIR):$(CLANG_LIBDIR):$(QTC_LIBDIR):$(QTC_LIBDIR_2)"' {} \; ; \
)

# Build dependencies
REQUIRED_PACKAGES += developer/clang-13

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += runtime/clang-13
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
