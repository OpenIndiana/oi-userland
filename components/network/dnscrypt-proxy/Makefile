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
# Copyright 2016 Alexander Pyhalov
# Copyright 2017 Andreas Wacknitz
#
BUILD_BITS=	64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= dnscrypt-proxy
COMPONENT_VERSION= 1.9.5
COMPONENT_REVISION= 4
COMPONENT_SUMMARY= DNSCrypt client
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:e89f5b9039979ab392302faf369ef7593155d5ea21580402a75bbc46329d1bb6
COMPONENT_ARCHIVE_URL= \
  https://github.com/jedisct1/dnscrypt-proxy/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://dnscrypt.org/
COMPONENT_FMRI= service/network/dns/dnscrypt-proxy
COMPONENT_LICENSE= ISC
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/Services

include $(WS_TOP)/make-rules/common.mk

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_BINDIR.64=$(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR.64=$(CONFIGURE_PREFIX)/sbin

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(TEST_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
# Bogus dependency due to libssp
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += system/library
