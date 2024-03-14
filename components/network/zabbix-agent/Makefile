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
COMPONENT_VERSION=	6.2.7
COMPONENT_SUMMARY=	Zabbix agent
COMPONENT_PROJECT_URL=	http://www.zabbix.com/
COMPONENT_FMRI=		application/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		zabbix-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	zabbix-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:6d423810667b948ed22052d9aa84a035e2d4b92cbe8efdb669cac529806b722d
COMPONENT_ARCHIVE_URL=	https://cdn.zabbix.com/zabbix/sources/stable/6.2/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# because we patched an am file
COMPONENT_PREP_ACTION = ( cd $(@D) && aclocal -I m4 && autoconf && autoheader && automake -a && automake )

# Ugly hack for fixing problems with missing files in source directory
COMPONENT_POST_CONFIGURE_ACTION= $(CP) $(BUILD_DIR_$(BITS))/include/common/config.h $(SOURCE_DIR)/include/common/config.h

CONFIGURE_OPTIONS +=   --sysconfdir=/etc/zabbix
CONFIGURE_OPTIONS +=   --enable-ipv6
CONFIGURE_OPTIONS +=   --enable-agent

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
