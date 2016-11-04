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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= dnscrypt-proxy
COMPONENT_VERSION= 1.6.1
COMPONENT_SUMMARY= DNSCrypt client
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:895ac36f5d4898dabf0ed65e0a579d0aa4d9a9be9cca4dca7b573a0ff170919a
COMPONENT_ARCHIVE_URL= \
  https://github.com/jedisct1/dnscrypt-proxy/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://dnscrypt.org/
COMPONENT_FMRI= service/network/dns/dnscrypt-proxy
COMPONENT_LICENSE= ISC
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/Services

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --sysconfdir=/etc

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
