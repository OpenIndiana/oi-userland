#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2012, Andrzej Szeszo
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cpp
COMPONENT_VERSION=      0.5.11
COMPONENT_REVISION=     2
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz

COMPONENT_FMRI=         developer/macro/cpp
COMPONENT_SUMMARY=      Solaris cpp
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_LICENSE_FILE= SUNWcpp.copyright
COMPONENT_LICENSE=      SUNWcpp.copyright

$(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE):
	$(IPS2TGZ) $(COMPONENT_SRC) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) https://pkg.openindiana.org/legacy \
	developer/macro/cpp@0.5.11,5.11-0.134:20100302T014816Z

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

build:	prep

install:	build
	@$(MKDIR) $(PROTO_DIR)
	@$(CP) -RP $(COMPONENT_SRC)/$(MACH)/* $(PROTO_DIR) || true

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
