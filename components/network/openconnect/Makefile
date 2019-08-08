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
# Copyright 2016 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openconnect
# Commit timestamp and previous known release
COMPONENT_VERSION=	7.7.20161105
COMPONENT_REVISION=	4
COMPONENT_VERSION_TAG=	b8d3971124b5b2ecccaf727ecc48ba94b531df8e
COMPONENT_VERSION_TAGSHORT=	b8d3971
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_VERSION_TAGSHORT).tar.gz
COMPONENT_FMRI=		network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION_TAGSHORT)
COMPONENT_PROJECT_URL=	http://www.infradead.org/openconnect/index.html
COMPONENT_DOWNLOAD_URL=	http://git.infradead.org/users/dwmw2/$(COMPONENT_NAME).git
COMPONENT_ARCHIVE_HASH=	\
	sha256:9cf801fe365f2262bc39b3768e242a30541cbfbf026795d7962355df4bb6293f
COMPONENT_ARCHIVE_URL=	$(COMPONENT_DOWNLOAD_URL)/snapshot/$(COMPONENT_VERSION_TAGSHORT).tar.gz
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING.LGPL
COMPONENT_SUMMARY=	An SSL VPN client (intended to be) compatible with Cisco AnyConnect and Juniper Pulse

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) &&\
        autoreconf -fiv &&\
        $(RM) config.h )

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# Use OpenSSL, it allows more options on OI/Hipster that openconnect uses
CONFIGURE_OPTIONS +=	--with-system-cafile=/etc/certs/ca-certificates.crt
CONFIGURE_OPTIONS +=	--without-gnutls

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

$(TEST_$(BITS)): $(BUILD_$(BITS))
	cd $(BUILD_DIR_$(BITS)) && $(MAKE) check
	$(TOUCH) $@

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += network/vpnc-scripts
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/libp11
REQUIRED_PACKAGES += library/desktop/p11-kit
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += driver/network/header-tun
