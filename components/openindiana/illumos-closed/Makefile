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
# Copyright 2016 Adam Stevko 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-closed
COMPONENT_VERSION=	5.11
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	illumos-closed - illumos closed binaries
COMPONENT_PROJECT_URL=	https://www.openindiana.org/
COMPONENT_FMRI=		developer/illumos-closed
COMPONENT_CLASSIFICATION=Development/System
COMPONENT_LICENSE= 	binary

COMPONENT_ARCHIVE_1=            on-closed-bins-nd.$(MACH).tar.bz2
COMPONENT_ARCHIVE_URL_1= \
    http://dlc.openindiana.org/dlc.sun.com/osol/on/downloads/20100817/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1.i386= \
    sha256:da3ca1ea24972ba6a01169265d8d38a45789ed7cc45334bfe026c108b1d2ff56
COMPONENT_ARCHIVE_HASH_1.sparc= \
    sha256:88b8c4032c1d759abec98e346085e0ba350fa485f28a12ff63f247e4125916e3
COMPONENT_ARCHIVE_HASH_1=       $(COMPONENT_ARCHIVE_HASH_1.$(MACH))

COMPONENT_ARCHIVE_2=            on-closed-bins.$(MACH).tar.bz2
COMPONENT_ARCHIVE_URL_2= \
    http://dlc.openindiana.org/dlc.sun.com/osol/on/downloads/20100817/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2.i386= \
    sha256:18e82bace8481dca62586e4bdff7f6b44fc63b41443799929e4d4b2187e98535
COMPONENT_ARCHIVE_HASH_2.sparc= \
    sha256:ce5425387a61dbf6842f8278771f244d2b860786a9d296b72b61e6721f8b7398
COMPONENT_ARCHIVE_HASH_2=       $(COMPONENT_ARCHIVE_HASH_2.$(MACH))

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

CLEAN_PATHS += $(BUILD_DIR)

$(BUILD_32):
	$(MKDIR) $(BUILD_DIR_32)
	$(TOUCH) $@

$(INSTALL_32): $(BUILD_32)
	$(MKDIR) $(PROTO_DIR)/opt/onbld	&& \
	cd $(PROTO_DIR)/opt/onbld && \
	/usr/bin/gtar xjpf $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_1) && \
	/usr/bin/gtar xjpf $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_2) && \
	$(CP) $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_1) $(PROTO_DIR)/opt/onbld/closed && \
	$(CP) $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE_2) $(PROTO_DIR)/opt/onbld/closed
	$(TOUCH) $@

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
