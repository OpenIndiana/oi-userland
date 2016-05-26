#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

# Special thanks goes to Lou Picciano <Lou@Picciano.org> for additional testing
# and his guidance and Michal Hanula <michal@hanu.la> for further testing.
#
# Copyright (c) 2016, Adam Stevko <adam.stevko@gmail.com>

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zabbix-agent
COMPONENT_VERSION=	2.2.13
COMPONENT_SRC=		zabbix-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	zabbix-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0a272ad4de22368f9a77864e0a9fa566f76c872814e81845e16d4d24cd5452f4
COMPONENT_PROJECT_URL=	http://www.zabbix.com/
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/zabbix/files/ZABBIX%20Latest%20Stable/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download

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


build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TESTS_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
