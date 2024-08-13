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
# Copyright (c) 2016, Adam Stevko <adam.stevko@gmail.com>
# Copyright (c) 2024, Carsten Grzemba
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zabbix-server
COMPONENT_VERSION=	7.0.1
COMPONENT_SUMMARY=	Zabbix server
COMPONENT_PROJECT_URL=	http://www.zabbix.com/
COMPONENT_FMRI=		application/management/$(COMPONENT_NAME)
COMPONENT_FMRI_AGENT=		application/management/zabbix-agent
COMPONENT_FMRI_PROXY=		application/management/zabbix-proxy
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		zabbix-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	zabbix-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:bbc749cefb296ffdf7ff48cfafd41632113f97225c7966f4e043436fcbef8ea1
COMPONENT_ARCHIVE_URL=	https://cdn.zabbix.com/zabbix/sources/stable/$(basename $(COMPONENT_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

PKG_VARS += COMPONENT_FMRI_AGENT COMPONENT_FMRI_PROXY

include $(WS_MAKE_RULES)/common.mk

# because we patched an am file
COMPONENT_PREP_ACTION = ( cd $(@D) && aclocal -I m4 && autoconf && autoheader && automake -a && automake )

# Ugly hack for fixing problems with missing files in source directory
COMPONENT_POST_CONFIGURE_ACTION= $(CP) $(BUILD_DIR_$(BITS))/include/common/config.h $(SOURCE_DIR)/include/common/config.h

CONFIGURE_OPTIONS +=   --sysconfdir=/etc/zabbix
CONFIGURE_OPTIONS +=   --enable-ipv6
CONFIGURE_OPTIONS +=   --enable-server
CONFIGURE_OPTIONS +=   --enable-agent
CONFIGURE_OPTIONS +=   --enable-proxy
CONFIGURE_OPTIONS +=   --with-postgresql
CONFIGURE_OPTIONS +=   --with-libevent
CONFIGURE_OPTIONS +=   --with-libevent-include=/usr/include/libevent2
CONFIGURE_OPTIONS +=   --with-net-snmp
CONFIGURE_OPTIONS +=   --with-libcurl
CONFIGURE_OPTIONS +=   --with-libxml2
CONFIGURE_OPTIONS +=   --with-openssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS +=   --with-ldap

COMPONENT_POST_INSTALL_ACTION = (cd $(SOURCE_DIR)/ui && \
	mkdir -p $(PROTOUSRSHAREDIR)/zabbix/html && \
	cp -rp * $(PROTOUSRSHAREDIR)/zabbix/html;);
COMPONENT_POST_INSTALL_ACTION += (cd $(SOURCE_DIR)/database && \
	mkdir -p $(PROTOUSRSHAREDIR)/zabbix-sql-scripts && \
	cp -rp * $(PROTOUSRSHAREDIR)/zabbix-sql-scripts;);
COMPONENT_POST_INSTALL_ACTION += (cd $(SOURCE_DIR)/man && \
		for f in zabbix_proxy ; do cp $${f}.man $(PROTOUSRSHAREMANDIR)/man8/$${f}.8; done; );

# Manually added build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
