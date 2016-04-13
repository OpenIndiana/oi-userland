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

COMPONENT_NAME= WorldTime
COMPONENT_VERSION= 0.9.2
COMPONENT_SUMMARY=  WorldTime gdesklet widget
COMPONENT_SRC=  WorldTime-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:9380eb61792fbadeee251737030264f4c74589af9c535102620cd3b119be646b
COMPONENT_ARCHIVE_URL= \
  http://www.gdesklets.info/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gdesklets.info/archive/
COMPONENT_FMRI = gnome/desklet/worldtime
CLEAN_PATHS+=$(COMPONENT_SRC)
CLEAN_PATHS+=$(BUILD_DIR)
COMPONENT_LICENSE = unknown
COMPONENT_LICENSE_FILE = worldtime.license
COMPONENT_CLASSIFICATION = Applications/Panels and Applets

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(TOUCH) $@

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:      $(BUILD_DIR)/%/.built
	$(RM) -r $(PROTO_DIR)
	$(MKDIR) $(PROTO_DIR)/usr/share/gdesklets/Displays
	cp -a $(COMPONENT_DIR)/$(COMPONENT_SRC) $(PROTO_DIR)/usr/share/gdesklets/Displays
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)
