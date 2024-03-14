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

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				qtcreator
COMPONENT_VERSION_MAJOR=	7.0
COMPONENT_VERSION_MINOR=	2
COMPONENT_VERSION=			$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
COMPONENT_SUMMARY=			QT Creator - A Cross-platform IDE for Application Development
COMPONENT_PROJECT_URL=		https://www.qt.io/product/development-tools
COMPONENT_SRC=				qt-creator-opensource-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=			$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=		sha256:14dee285aa3aa56fb25ccbd7587382fb6cb05ae99a1a30237f0a0bbef3ceff7a
COMPONENT_ARCHIVE_URL=		https://download.qt.io/archive/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=				editor/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=      	GPL-3.0-only
COMPONENT_LICENSE_FILE=		LICENSE.GPL3-EXCEPT

TEST_TARGET= $(NO_TESTS)

# qtcreator 7.0.2 cannot be compiled using neither clang-15 nor clang-17 so force clang-13
CLANG_VERSION = 13

include $(WS_MAKE_RULES)/common.mk

PATH= $(QT5_BINDIR):$(PATH.gnu)
CXXFLAGS += -fPIC
CXXFLAGS += -I$(GCC_INCGXXDIR)
LDFLAGS += -lxnet
LDFLAGS += -Wl,-rpath,$(QT5_LIBDIR):$(CLANG_LIBDIR):/usr/lib/amd64/qtcreator:/usr/lib/amd64/qtcreator/plugins

COMPONENT_INSTALL_ENV+= INSTALL_ROOT=$(PROTOUSRDIR)

COMPONENT_PRE_CMAKE_ACTION += $(CP) -r $(SOURCE_DIR)/* $(@D)/
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DCMAKE_PREFIX_PATH="$(QT5_LIBDIR)/cmake;$(CLANG_PREFIX)"
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=$(USRDIR)
CMAKE_OPTIONS += -DPython3_EXECUTABLE=$(PYTHON)
CMAKE_OPTIONS += -DWITH_DOCS=ON
CMAKE_OPTIONS += -DBUILD_DEVELOPER_DOCS=ON
CMAKE_OPTIONS += -DBUILD_QBS=OFF
CMAKE_OPTIONS += -DQTC_CLANG_BUILDMODE_MATCH=ON

COMPONENT_POST_INSTALL_ACTION = \
	$(CHMOD) +x $(PROTOUSRBINDIR)/*; \
	$(CHMOD) +x $(PROTOUSRDIR)/libexec/*


$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CMAKE_ACTION)
	(cd $(@D) ; $(ENV) $(CMAKE_ENV) \
		$(CMAKE) $(CMAKE_OPTIONS) $(@D))
	$(COMPONENT_POST_CMAKE_ACTION)
	$(TOUCH) $@

# Auto-generated dependencies
REQUIRED_PACKAGES += $(CLANG_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/yaml-cpp
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
