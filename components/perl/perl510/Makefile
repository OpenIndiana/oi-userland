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

COMPONENT_NAME=         perl-510
COMPONENT_VERSION=      5.10.0
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
# below is required for userland-fetch to bahave
COMPONENT_ARCHIVE_URL=blah

download::
	$(IPS2TGZ) $(COMPONENT_SRC) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) http://pkg.openindiana.org/hipster \
	pkg://openindiana.org/runtime/perl-510@5.10.0,5.11-0.151.1.8:20130305T141236Z \
	pkg://openindiana.org/runtime/perl-510/extra@5.10.0,5.11-0.151.1.8:20130305T141244Z


include ../../../make-rules/prep.mk
include ../../../make-rules/ips.mk

build:	prep

install:	build
	@$(MKDIR) $(PROTO_DIR)
	@$(CP) -RP $(COMPONENT_SRC)/$(MACH)/* $(PROTO_DIR) || true

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)
