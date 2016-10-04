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

COMPONENT_LICENSE =	Apache2-or-GPLv3
COMPONENT_LICENSE_FILE = LICENSE
# COMPONENT_LICENSE_FILE += LICENSE_Apache2.txt
# COMPONENT_LICENSE_FILE += LICENSE_GPLv3.txt
# COMPONENT_LICENSE_FILE += LICENSE_KST32B_v2.txt
# COMPONENT_LICENSE_FILE += license-lc_opengost-fonts.txt
# COMPONENT_LICENSE_FILE += LICENSE-MIT.txt
# COMPONENT_LICENSE_FILE += gpl-2.0.txt
# COMPONENT_LICENSE_FILE += gpl-2.0greater.txt

COMPONENT_SUMMARY =	LibreCAD is a 2D CAD drawing tool based on the community edition of QCAD.
COMPONENT_CLASSIFICATION = Applications/Graphics and Imaging

COMPONENT_REVISION = $(shell cd $(COMPONENT_SRC); git rev-list HEAD --count)
IPS_COMPONENT_VERSION = $(COMPONENT_VERSION)

include ../../../make-rules/prep.mk
include ../../../make-rules/justmake.mk

# publish: update-publish
include ../../../make-rules/ips.mk

tolower = $(shell echo $(1) | tr '[A-Z]' '[a-z]')
COMPONENT_PRE_INSTALL_ACTION += ginstall -d $(PROTO_DIR)$(USRBINDIR);
COMPONENT_PRE_INSTALL_ACTION += ginstall -d $(PROTO_DIR)$(USRLIBDIR)/$(call tolower, $(COMPONENT_NAME))/resources
COMPONENT_PRE_INSTALL_ACTION +=  ginstall -d $(PROTO_DIR)$(USRSHAREDOCDIR)/$(call tolower, $(COMPONENT_NAME))
COMPONENT_INSTALL_ACTION = \
	ginstall -m 755 $(@D)/unix/librecad $(PROTO_DIR)$(USRBINDIR); \
	  ginstall -m 755 $(@D)/unix/ttf2lff $(PROTO_DIR)$(USRBINDIR); \
          gcp -rf  $(@D)/unix/resources/* \
                  $(PROTO_DIR)$(USRLIBDIR)/$(call tolower, $(COMPONENT_NAME))/resources; \
          gcp -rf  $(@D)/librecad/support/* \
                  $(PROTO_DIR)$(USRLIBDIR)/$(call tolower, $(COMPONENT_NAME))/resources; \
	  cd $(PROTO_DIR)$(USRLIBDIR)/$(call tolower, $(COMPONENT_NAME))/resources/plugins && mkdir 64 && mv lib*so 64; \
	  cd $(PROTO_DIR)$(USRLIBDIR)/$(call tolower, $(COMPONENT_NAME))/resources/ && mv fonts $(PROTO_DIR)$(USRSHAREDOCDIR)/$(call tolower, $(COMPONENT_NAME)); \
          cd $(SOURCE_DIR) && cp -p  LICENSE* gpl-* license* \
		$(PROTO_DIR)$(USRSHAREDOCDIR)/$(call tolower, $(COMPONENT_NAME))
	
COMPONENT_PRE_BUILD_ACTION = \
        (cd $(@D) && qmake $(call tolower,$(COMPONENT_NAME)).pro)

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
