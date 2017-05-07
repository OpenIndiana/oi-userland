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
# Copyright 2016 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vpnc-scripts
# Commit timestamp and previous known release (none here)
COMPONENT_VERSION=	0.0.20160828
COMPONENT_REVISION=	2
COMPONENT_VERSION_TAG=	6e04e0bbb66c0bf0ae055c0f4e58bea81dbb5c3c
COMPONENT_VERSION_TAGSHORT=	6e04e0b
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_VERSION_TAGSHORT).tar.gz
COMPONENT_FMRI=		network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION_TAGSHORT)
COMPONENT_PROJECT_URL=	http://www.infradead.org/openconnect/$(COMPONENT_NAME).html
COMPONENT_DOWNLOAD_URL=	http://git.infradead.org/users/dwmw2/$(COMPONENT_NAME).git
COMPONENT_ARCHIVE_HASH=	\
	sha256:988b0cbc469bdd5cb2a5af3048781e6d3b8dcd89fb9b03798ab8365d34717246
COMPONENT_ARCHIVE_URL=	$(COMPONENT_DOWNLOAD_URL)/snapshot/$(COMPONENT_VERSION_TAG).tar.gz
COMPONENT_LICENSE=		GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_SUMMARY=	Connect scripts for use with vpnc and openconnect (and similar clients)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

# This is an archive with scripts, nothing to build
$(BUILD_$(BITS)): $(SOURCE_DIR)/.prep
	$(MKDIR) $(BUILD_DIR_$(BITS))
	$(TOUCH) $@

build: $(BUILD_32)

# By convention (consumer defaults), this lands under /etc/vpnc/
# The other scripts (vpnc-script-ptrtd and vpnc-script-ssh) and
# the netunshare.c program are at the moment extremely linux
# oriented so we don't even package them.
$(INSTALL_32): $(BUILD_32) $(SOURCE_DIR)/.prep
	$(MKDIR) $(PROTOETCDIR)/vpnc
	$(CP) $(SOURCE_DIR)/vpnc-script $(PROTOETCDIR)/vpnc/
	$(CP) $(SOURCE_DIR)/vpnc-script-win.js $(PROTOETCDIR)/vpnc/
	$(CP) $(SOURCE_DIR)/xinetd.netns.conf $(PROTOETCDIR)/vpnc/xinetd.netns.conf.example
	$(TOUCH) $@

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
