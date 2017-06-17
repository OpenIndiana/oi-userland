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
# Copyright 2017 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         eclipse
COMPONENT_VERSION=      4.6.3
COMPONENT_SUMMARY=      Eclipse IDE for Java, C/C++, Python, JavaScript and PHP
COMPONENT_PROJECT_URL=  https://eclipse.org/
COMPONENT_FMRI=         developer/eclipse
COMPONENT_CLASSIFICATION=Development/Editors
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_DATE= 201703010400
COMPONENT_ARCHIVE_URL= \
  http://mirrors.nic.cz/eclipse/eclipse/downloads/drops4/R-$(COMPONENT_VERSION)-$(COMPONENT_ARCHIVE_DATE)/eclipse-platform-$(COMPONENT_VERSION)-solaris-gtk-x86_64.zip
COMPONENT_ARCHIVE_HASH= \
  sha512:c047b216c419a0460ab11e73b6d6098126fcc81d6f0f746fc07ed983afbed6e366a39cd025874d153cb3bd51082c2a8e905ca44a3e534382510df926d5328e53
COMPONENT_LICENSE=      EPLv1, EDLv1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

ECLIPSE_DIR= $(PROTO_DIR)/opt/eclipse

# Do not create backup files
GPATCH_BACKUP=

$(BUILD_32): $(SOURCE_DIR)/.prep
	@$(RM) -r $(@D) ; $(MKDIR) $(@D)
	@$(TOUCH) $@

$(INSTALL_32):  $(BUILD_32)
	@$(MKDIR) $(ECLIPSE_DIR)
	@$(CP) -RP $(COMPONENT_SRC)/* $(ECLIPSE_DIR) || true
	@$(GSED) -i -e '1 s,/usr/bin/python,$(PYTHON),' $(PROTO_DIR)/opt/eclipse/plugins/org.apache.ant_1.9.6.v201510161327/bin/runant.py
	@$(TOUCH) $@

build:	$(BUILD_32)

install:	$(INSTALL_32)

clean::
	@$(RM) -rf $(SOURCE_DIR) $(BUILD_DIR) 

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
