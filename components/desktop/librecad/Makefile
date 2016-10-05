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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	LibreCAD
COMPONENT_VERSION =	2.1.3
COMPONENT_PROJECT_URL =	https://github.com/LibreCAD
COMPONENT_FMRI =		desktop/librecad
COMPONENT_SRC =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5d0bc37efa1006742785c06ec30737c7866b0366048553c5560e06a3e442f7b3
COMPONENT_ARCHIVE_URL=  https://api.github.com/repos/$(COMPONENT_NAME)/$(COMPONENT_NAME)/tarball/$(COMPONENT_VERSION)

UNPACK_ARGS = --relocate-to=$(COMPONENT_SRC)
COMPONENT_POST_UNPACK_ACTION = \
	$(MV) $(COMPONENT_SRC)/*/* $(COMPONENT_SRC) ;\
	$(MV) $(COMPONENT_SRC)/*/.[gt]* $(COMPONENT_SRC) ;\
	rmdir $(COMPONENT_SRC)/$(COMPONENT_NAME)-$(COMPONENT_NAME)-[0-9a-f]*

COMPONENT_LICENSE =	GPLv2
COMPONENT_LICENSE_FILE = LICENSE
# COMPONENT_LICENSE_FILE += Apache2
# COMPONENT_LICENSE_FILE += LICENSE_GPLv3.txt
# COMPONENT_LICENSE_FILE += LICENSE_KST32B_v2.txt
# COMPONENT_LICENSE_FILE += license-lc_opengost-fonts.txt
# COMPONENT_LICENSE_FILE += LICENSE-MIT.txt
# COMPONENT_LICENSE_FILE += gpl-2.0.txt
# COMPONENT_LICENSE_FILE += gpl-2.0greater.txt

COMPONENT_SUMMARY =	LibreCAD is a 2D CAD drawing tool based on the community edition of QCAD.
COMPONENT_CLASSIFICATION = Applications/Graphics and Imaging

IPS_COMPONENT_VERSION = $(COMPONENT_VERSION)

include ../../../make-rules/prep.mk
include ../../../make-rules/justmake.mk
include ../../../make-rules/ips.mk

COMPONENT_NAME_lc = $(shell echo $(COMPONENT_NAME) | tr '[A-Z]' '[a-z]')
COMPONENT_INSTALL_ACTION = \
	ginstall -Dpm 755 $(@D)/unix/librecad $(PROTO_DIR)$(USRBINDIR)/librecad; \
	ginstall -Dpm 755 $(@D)/unix/ttf2lff $(PROTO_DIR)$(USRBINDIR)/ttf2lff; \
	ginstall -d $(PROTO_DIR)$(USRLIBDIR)/$(COMPONENT_NAME_lc)/plugins/$(MACH64) ; \
	ginstall -d $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME_lc); \
        gcp -rfL  $(@D)/unix/resources/plugins/* \
                  $(PROTO_DIR)$(USRLIBDIR)/$(COMPONENT_NAME_lc)/plugins/$(MACH64)/; \
        gcp -rfL  $(@D)/unix/resources/qm \
                  $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME_lc)/; \
        gcp -rfL  $(@D)/librecad/support/* \
                  $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME_lc); \
	ginstall -Dpm 644 $(@D)/desktop/librecad.desktop $(PROTO_DIR)$(USRSHAREDIR)/applications/librecad.desktop ; \
	ginstall -Dpm 644 $(@D)/librecad/res/main/librecad.png $(PROTO_DIR)$(USRSHAREDIR)/pixmaps/librecad.png ; \
	ginstall -Dpm 644 $(@D)/desktop/librecad.sharedmimeinfo $(PROTO_DIR)$(USRSHAREDIR)/mime/packages/librecad.xml ; \
	ginstall -Dpm 644 $(@D)/desktop/librecad.1 $(PROTO_DIR)$(USRSHAREMANDIR)/man1/librecad.1 ; \
	ginstall -Dpm 644 $(SOURCE_DIR)/ttf2lff.1 $(PROTO_DIR)$(USRSHAREMANDIR)/man1/ttf2lff.1 ; \
        ginstall -Dpm 644  $(SOURCE_DIR)/LICENSE* $(SOURCE_DIR)/gpl-* $(SOURCE_DIR)/license* \
	  $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME_lc)/doc
	
	
COMPONENT_PRE_BUILD_ACTION = \
        (cd $(@D) && qmake $(COMPONENT_NAME_lc).pro 'CONFIG+=release')

build:		$(BUILD_32)

install:	$(INSTALL_32)

REQUIRED_PACKAGES += library/qt4
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += library/boost
REQUIRED_PACKAGES += library/muparser
