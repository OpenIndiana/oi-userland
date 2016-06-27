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

COMPONENT_NAME=		ngrep
COMPONENT_VERSION=	1.45
COMPONENT_SUMMARY=	ngrep strives to provide most of GNU grep common features, applying them to the network layer
COMPONENT_PROJECT_URL=	http://ngrep.sourceforge.net/
COMPONENT_FMRI=		diagnostic/ngrep
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/ngrep/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download	
COMPONENT_ARCHIVE_HASH=	sha256:aea6dd337da8781847c75b3b5b876e4de9c58520e0d77310679a979fc6402fa7
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION= \
	$(CLONEY) $(SOURCE_DIR) $(@D)

CONFIGURE_OPTIONS+= --enable-ipv6
CONFIGURE_OPTIONS+= --enable-pcre
CONFIGURE_OPTIONS+= --with-dropprivs-user=nobody
CONFIGURE_OPTIONS+= --with-pcap-includes=/usr/include/pcap

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
