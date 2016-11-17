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
# Copyright 2016 Andrey Sokolov. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		asterisk
COMPONENT_VERSION=	1.8.32.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3c12ddbb86e2b901af449bd5a3ac7bbc55a28664159d0c4fb70f89d761d8bf9e
COMPONENT_PROJECT_URL=	http://www.asterisk.org
COMPONENT_ARCHIVE_URL=	http://downloads.asterisk.org/pub/telephony/asterisk/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

PATCH_LEVEL = 0

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--without-oss
CONFIGURE_OPTIONS +=	--with-gsm=internal

COMPONENT_INSTALL_TARGETS += samples

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
