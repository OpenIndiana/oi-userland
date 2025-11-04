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
# Copyright 2025, Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         as
COMPONENT_VERSION=      0.5.11
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=	Sun as
COMPONENT_PROJECT_URL=	https://www.openindiana.org/
COMPONENT_FMRI=		developer/as
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME).tar.gz
COMPONENT_ARCHIVE_URL=	http://dlc.openindiana.org/dlc.sun.com/osol/on/downloads/20100817/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:1758eb4721981d76c86dfe05b20d8dbccadc5938800554d2d54768e90fb7b623


include ../../../make-rules/prep.mk
include ../../../make-rules/ips.mk

build:	prep

install:	build
	@$(MKDIR) $(PROTO_DIR)
	@$(CP) -RP $(COMPONENT_SRC)/$(MACH)/* $(PROTO_DIR) || true

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
