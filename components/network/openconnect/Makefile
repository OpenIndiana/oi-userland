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
# Copyright 2019 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS= 64
OPENSSL_VERSION= 3.1
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openconnect
COMPONENT_VERSION=	9.12
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	An SSL VPN client (intended to be) compatible with Cisco AnyConnect and Juniper Pulse
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.infradead.org/openconnect
COMPONENT_ARCHIVE_HASH=	sha256:a2bedce3aa4dfe75e36e407e48e8e8bc91d46def5335ac9564fbf91bd4b2413e
COMPONENT_ARCHIVE_URL=	https://www.infradead.org/openconnect/download/$(COMPONENT_ARCHIVE)
# COMPONENT_ARCHIVE_URL=	https://github.com/openconnect/openconnect/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING.LGPL

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION = \
	(cd $(@D) && \
	autoreconf -fiv && \
	$(RM) config.h )

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# To prevent "libtool_install_magic: unbound variable"
unexport SHELLOPTS

# Use OpenSSL, it allows more options on OI/Hipster that openconnect uses
CONFIGURE_OPTIONS += --with-system-cafile=/etc/certs/ca-certificates.crt
CONFIGURE_OPTIONS += --without-gnutls
CONFIGURE_OPTIONS += --without-libpcsclite

# Replace python3 shebang lines with properly versioned ones.
COMPONENT_POST_INSTALL_ACTION += \
	for file in $(PROTO_DIR)/usr/libexec/openconnect/*.py ; do \
	$(GSED) -i 's/python3/python$(PYTHON_VERSION)/' $$file ; \
	done  ;

# Manually added dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += network/vpnc-scripts
REQUIRED_PACKAGES += driver/network/header-tun

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
