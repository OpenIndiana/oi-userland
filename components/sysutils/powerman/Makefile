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
# Copyright 2023 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	powerman
COMPONENT_VERSION=	2.3.25
COMPONENT_SUMMARY=	Powerman - power management software ($(COMPONENT_VERSION))
COMPONENT_DESCRIPTION=	LLNL CHAOS powerman is free UNIX/Linux software that controls (remotely and in parallel) switched power distribution units
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:36e98a5a6b1395d8243b5bcaa8a6af42b4ab9411a63d7aa0768b4014ee0f207d
COMPONENT_ARCHIVE_URL=	\
  https://github.com/chaos/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/chaos/powerman
COMPONENT_FMRI=	system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	GPLv2+
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += CPPFLAGS="-DNETSNMP_DISABLE_MD5"

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--with-httppower
CONFIGURE_OPTIONS +=	--with-snmppower
CONFIGURE_OPTIONS +=	--with-systemdsystemunitdir=no

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^\# TOTAL/p" ' \
	'-e "/^\# PASS/p" ' \
	'-e "/^\# SKIP/p" ' \
	'-e "/^\# XFAIL/p" ' \
	'-e "/^\# FAIL/p" ' \
	'-e "/^\# XPASS/p" ' \
	'-e "/^\# ERROR/p" '

# libgenders is another CHAOS project that we don't bother to package for now.
# It is a static cluster configuration database used for cluster configuration
# management. It is used by a variety of tools and scripts for management of
# large clusters.
CONFIGURE_OPTIONS +=	--without-genders

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
