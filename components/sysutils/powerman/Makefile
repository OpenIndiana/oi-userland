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

COMPONENT_NAME=	powerman
COMPONENT_VERSION=	2.3.24
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Powerman - power management software ($(COMPONENT_VERSION))
COMPONENT_DESCRIPTION=	LLNL CHAOS powerman is free UNIX/Linux software that controls (remotely and in parallel) switched power distribution units
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:d2f08ee1383d417ed14438443fefbad4954a3912de8e8e574a21089927eda2a0
COMPONENT_ARCHIVE_URL=	\
  https://github.com/chaos/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://github.com/chaos/powerman
COMPONENT_FMRI=	system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	GPLv2+
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk


COMPONENT_PREP_ACTION =	( cd $(SOURCE_DIR) && ./autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION =	( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--with-httppower
CONFIGURE_OPTIONS +=	--with-snmppower
CONFIGURE_OPTIONS +=	--with-systemdsystemunitdir=no

# libgenders is another CHAOS project that we don't bother to package for now.
# It is a static cluster configuration database used for cluster configuration
# management. It is used by a variety of tools and scripts for management of
# large clusters.
CONFIGURE_OPTIONS +=	--without-genders


build: $(BUILD_32_and_64)

# Ensure configs etc. match 32-bit
$(INSTALL_32): $(INSTALL_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
