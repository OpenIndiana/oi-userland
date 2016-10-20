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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tor
COMPONENT_VERSION=	0.2.8.9
COMPONENT_PROJECT_URL=	https://www.torproject.org
COMPONENT_SUMMARY=	Anonymizing overlay network for TCP
COMPONENT_FMRI=		network/tor
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3f5c273bb887be4aff11f4d99b9e2e52d293b81ff4f6302b730161ff16dc5316
COMPONENT_ARCHIVE_URL=	https://www.torproject.org/dist/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc	
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	BSD, OPEN DATA LICENSE

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-bufferevents
CONFIGURE_OPTIONS+=	--enable-buf-freelists
#CONFIGURE_OPTIONS+=	--enable-linker-hardening
CONFIGURE_OPTIONS+=	--localstatedir=/var

CFLAGS += -D_FILE_OFFSET_BITS=64

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk

REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/math
