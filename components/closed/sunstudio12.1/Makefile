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
# Copyright 2012, Andrzej Szeszo
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sunstudio12u1
COMPONENT_VERSION=	12.1.1
COMPONENT_REVISION=	5
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
# below is required for userland-fetch to bahave
COMPONENT_ARCHIVE_URL=blah

download::
	$(IPS2TGZ) $(COMPONENT_SRC) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) http://pkg.openindiana.org/legacy \
	pkg://opensolaris.org/developer/sunstudio12u1@12.1.1,5.11-0.111:20100306T002245Z

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

$(SOURCE_DIR)/build/$(MACH)/.installed:
	@$(MKDIR) $(PROTO_DIR)
	@$(CP) -RP $(COMPONENT_SRC)/$(MACH)/* $(PROTO_DIR)
	@$(MKDIR) $(@D)
	@$(TOUCH) $@

build:	prep

install:	build	$(SOURCE_DIR)/build/$(MACH)/.installed

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/library/xprofile
REQUIRED_PACKAGES += developer/sunstudio12u1/backend
REQUIRED_PACKAGES += developer/sunstudio12u1/library/f90-libs
REQUIRED_PACKAGES += developer/sunstudio12u1/library/math-libs
REQUIRED_PACKAGES += diagnostic/cpu-counters
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += service/picl
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++/sunpro
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/mtsk
