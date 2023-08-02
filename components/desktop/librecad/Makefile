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
# Copyright 2016 Carsten Grzemba cgrzemba@opencsw.org
#

BUILD_BITS=64
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	LibreCAD
COMPONENT_VERSION =     2.2.0-rc1
COMPONENT_REVISION=     3
IPS_COMPONENT_VERSION = 2.2.0.1
COMPONENT_PROJECT_URL =	https://github.com/LibreCAD
COMPONENT_FMRI =	desktop/librecad
COMPONENT_SRC =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = \
   sha256:2c937a9423ecf501902ef74c722ec413562e47c45125ac87257f02942d0676ea
COMPONENT_ARCHIVE_URL=	https://github.com/LibreCAD/LibreCAD/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_SUMMARY=	LibreCAD is a 2D CAD drawing tool based on the community edition of QCAD.
COMPONENT_CLASSIFICATION= Applications/Graphics and Imaging

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH.qt5 = /usr/lib/qt/5.15/bin/$(MACH64)
PATH=$(GCC_BINDIR):$(PATH.qt5):$(PATH.illumos)

COMPONENT_NAME_lc = $(shell echo $(COMPONENT_NAME) | tr '[A-Z]' '[a-z]')
COMPONENT_INSTALL_ACTION = \
	$(INSTALL) -Dpm 755 $(@D)/unix/librecad $(PROTO_DIR)$(USRBINDIR)/librecad; \
	$(INSTALL) -Dpm 755 $(@D)/unix/ttf2lff $(PROTO_DIR)$(USRBINDIR)/ttf2lff; \
	$(INSTALL) -d $(PROTO_DIR)$(USRLIBDIR)/$(COMPONENT_NAME_lc)/plugins/$(MACH64) ; \
	$(INSTALL) -d $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME_lc); \
	$(CP) -rfL  $(@D)/unix/resources/plugins/* \
		$(PROTO_DIR)$(USRLIBDIR)/$(COMPONENT_NAME_lc)/plugins/$(MACH64)/; \
	$(CP) -rfL  $(@D)/unix/resources/qm \
		$(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME_lc)/; \
	$(CP) -rfL  $(@D)/librecad/support/* \
		$(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME_lc); \
	$(INSTALL) -Dpm 644 $(@D)/desktop/librecad.desktop $(PROTO_DIR)$(USRSHAREDIR)/applications/librecad.desktop ; \
	$(INSTALL) -Dpm 644 $(@D)/librecad/res/main/librecad.png $(PROTO_DIR)$(USRSHAREDIR)/pixmaps/librecad.png ; \
	$(INSTALL) -Dpm 644 $(@D)/desktop/librecad.sharedmimeinfo $(PROTO_DIR)$(USRSHAREDIR)/mime/packages/librecad.xml ; \
	$(INSTALL) -Dpm 644 $(@D)/desktop/librecad.1 $(PROTO_DIR)$(USRSHAREMANDIR)/man1/librecad.1 ; \
	$(INSTALL) -Dpm 644 $(SOURCE_DIR)/ttf2lff.1 $(PROTO_DIR)$(USRSHAREMANDIR)/man1/ttf2lff.1 ; \
	$(INSTALL) -Dpm 644  $(SOURCE_DIR)/licenses/* \
	  $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME_lc)/doc

COMPONENT_PRE_BUILD_ACTION = \
        (cd $(@D) && qmake $(COMPONENT_NAME_lc).pro 'CONFIG+=release')

# Build dependencies
REQUIRED_PACKAGES += system/library/boost

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
