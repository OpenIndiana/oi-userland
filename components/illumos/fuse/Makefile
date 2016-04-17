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
# Copyright 2016, Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-fusefs
COMPONENT_VERSION=	1.3
COMPONENT_SRC=		$(COMPONENT_NAME)-Version-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha256:29fd2dff679b4da58dbc0830730a6ac54d4a0fdeb91459d8341594db94f4c058
COMPONENT_ARCHIVE_URL=	https://github.com/jurikm/illumos-fusefs/archive/Version-$(COMPONENT_VERSION).zip

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/opt/onbld/bin/i386:/opt/onbld/bin:/usr/gnu/bin:/usr/bin:/usr/sbin:/sbin

$(BUILD_32):    $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	(cd $(@D)/kernel && dmake)
	$(TOUCH) $@

$(INSTALL_32): $(BUILD_32)
	$(MKDIR) $(PROTO_DIR)
	
	(cd $(@D)/kernel && dmake install)
	
	$(MKDIR) $(PROTOUSRKERNELDRVDIR) $(PROTOUSRKERNELDRVDIR64)

	$(INSTALL) $(@D)/kernel/proto/$(USRKERNELDRVDIR)/fuse $(PROTOUSRKERNELDRVDIR)
	$(INSTALL) $(@D)/kernel/proto/$(USRKERNELDRVDIR64)/fuse $(PROTOUSRKERNELDRVDIR64)
	$(INSTALL) $(@D)/kernel/proto/$(USRKERNELDRVDIR)/fuse.conf $(PROTOUSRKERNELDRVDIR)

	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)

