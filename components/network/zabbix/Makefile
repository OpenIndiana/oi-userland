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
# Copyright (c) 2019, Till Wegmueller <toasterson@gmail.com>

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zabbix
COMPONENT_VERSION=	4.0.5
COMPONENT_SRC=		zabbix-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	zabbix-$(COMPONENT_VERSION).tar.gz
COMPONENT_SUMMARY=	Zabbix the Enterprise class monitoring system
COMPONENT_FMRI=		application/management/zabbix
COMPONENT_ARCHIVE_HASH= sha256:55e7e218e170dd085ae1d642d4e90dc3576011fa3ce72407425cb73003c31906
COMPONENT_PROJECT_URL=	http://www.zabbix.com/
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/zabbix/files/ZABBIX%20Latest%20Stable/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_CLASSIFICATION=org.opensolaris.category.2008:Applications/System Utilities
COMPONENT_LICENSE_FILE= zabbix.license
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Ugly hack for fixing problems with missing files in source directory
CONFIGURE_SCRIPT=	$(BUILD_DIR_$(BITS))/configure

CONFIGURE_OPTIONS +=    --sysconfdir=/etc/zabbix
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--enable-agent
CONFIGURE_OPTIONS +=	--enable-server
CONFIGURE_OPTIONS +=	--enable-proxy
CONFIGURE_OPTIONS +=	--enable-java
#CONFIGURE_OPTIONS +=	--with-mysql=/usr/mariadb/10.3
CONFIGURE_OPTIONS +=	--with-postgresql
CONFIGURE_OPTIONS +=	--with-libpcre-include=/usr/include/pcre
#CONFIGURE_OPTIONS +=	--with-sqlite3

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TESTS_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
#REQUIRED_PACKAGES += database/mariadb-103
REQUIRED_PACKAGES += database/postgres-11/developer
#REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += library/pcre
