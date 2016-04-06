#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= gdesklets
COMPONENT_VERSION= 0.36.3
# Version was bumped in JDS
IPS_COMPONENT_VERSION= 2.30.0
COMPONENT_SUMMARY= Applications/Panels and Applets
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:805b0343635e5dcfd24d23ab10f0153ab5135dc971ba1712fbf4bddbeee26af5
COMPONENT_ARCHIVE_URL= \
  https://launchpad.net/gdesklets/0.3x/release-of-$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://launchpad.net/gdesklets
COMPONENT_CLASSIFICATION = Applications/Panels and Applets
COMPONENT_FMRI = gnome/desklet/gdesklets
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

COMPONENT_PRE_CONFIGURE_ACTION =        (chmod -R u+r $(SOURCE_DIR) && cp -rp $(SOURCE_DIR)/* $(@D) && \
					cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
					cd $(@D)/po-sun && $(MAKE) all )

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build: $(BUILD_32)

install: $(INSTALL_32)
