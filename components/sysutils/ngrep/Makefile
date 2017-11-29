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
COMPONENT_VERSION=	1.47
COMPONENT_SRC_VERSION=	1_47
COMPONENT_SUMMARY=	ngrep strives to provide most of GNU grep common features, applying them to the network layer
COMPONENT_PROJECT_URL=	https://github.com/jpr5/ngrep
COMPONENT_FMRI=		diagnostic/ngrep
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_SRC_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  $(COMPONENT_PROJECT_URL)/archive/V$(COMPONENT_SRC_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:dc4dbe20991cc36bac5e97e99475e2a1522fd88c59ee2e08f813432c04c5fff3
COMPONENT_LICENSE=	BSD

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
