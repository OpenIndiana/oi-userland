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
# Copyright 2023 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-closed
COMPONENT_VERSION=	5.11
COMPONENT_REVISION=	5
COMPONENT_SUMMARY=	illumos-closed - illumos closed binaries
COMPONENT_PROJECT_URL=	https://www.openindiana.org/
COMPONENT_FMRI=		developer/illumos-closed
COMPONENT_CLASSIFICATION=Development/System
COMPONENT_LICENSE= 	binary

COMPONENT_ARCHIVE_1=            on-closed-bins-nd.$(MACH).tar.bz2
COMPONENT_ARCHIVE_2=            on-closed-bins.$(MACH).tar.bz2
ifeq ($(strip $(MACH)),i386)
COMPONENT_ARCHIVE_URL_1= \
    http://dlc.openindiana.org/dlc.sun.com/osol/on/downloads/20100817/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1.i386= \
    sha256:da3ca1ea24972ba6a01169265d8d38a45789ed7cc45334bfe026c108b1d2ff56
COMPONENT_ARCHIVE_URL_2= \
    http://dlc.openindiana.org/dlc.sun.com/osol/on/downloads/20100817/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2.i386= \
    sha256:18e82bace8481dca62586e4bdff7f6b44fc63b41443799929e4d4b2187e98535
else
COMPONENT_ARCHIVE_URL_1= \
    https://dlc.openindiana.aurora-opencloud.org/SPARC/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1.sparc= \
    sha256:6b5030de3facfb4dd2e9bb5f82efbddba6cd9ff238fea1aba4c5401b4db59bab
COMPONENT_ARCHIVE_URL_2= \
    https://dlc.openindiana.aurora-opencloud.org/SPARC/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2.sparc= \
    sha256:6dfa3569dd1ca2e6168e02b9b1e7c224ea7ae4d868955a1b5deb1927e20077c0
endif
COMPONENT_ARCHIVE_HASH_1=       $(COMPONENT_ARCHIVE_HASH_1.$(MACH))
COMPONENT_ARCHIVE_HASH_2=       $(COMPONENT_ARCHIVE_HASH_2.$(MACH))

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

CLEAN_PATHS += $(BUILD_DIR)

PKG_HARDLINKS +=	opt/onbld/closed/root_i386/etc/init.d/llc2
PKG_HARDLINKS +=	opt/onbld/closed/root_i386/kernel/strmod/$(MACH64)/sdpib
PKG_HARDLINKS +=	opt/onbld/closed/root_i386/kernel/strmod/sdpib
PKG_HARDLINKS +=	opt/onbld/closed/root_i386/platform/i86pc/kernel/cpu/cpu_ms.GenuineIntel.6.46
PKG_HARDLINKS +=	opt/onbld/closed/root_i386/platform/i86pc/kernel/cpu/$(MACH64)/cpu_ms.GenuineIntel.6.46
PKG_HARDLINKS +=	opt/onbld/closed/root_i386/usr/xpg4/bin/alias
PKG_HARDLINKS +=	opt/onbld/closed/root_i386-nd/etc/init.d/llc2
PKG_HARDLINKS +=	opt/onbld/closed/root_i386-nd/kernel/drv/$(MACH64)/sdpib
PKG_HARDLINKS +=	opt/onbld/closed/root_i386-nd/kernel/drv/sdpib
PKG_HARDLINKS +=	opt/onbld/closed/root_i386-nd/platform/i86pc/kernel/cpu/cpu_ms.GenuineIntel.6.46
PKG_HARDLINKS +=	opt/onbld/closed/root_i386-nd/platform/i86pc/kernel/cpu/$(MACH64)/cpu_ms.GenuineIntel.6.46
PKG_HARDLINKS +=	opt/onbld/closed/root_i386-nd/usr/xpg4/bin/alias

$(BUILD_32): download
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
