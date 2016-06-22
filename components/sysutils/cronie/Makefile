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
# Copyright 2016 Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cronie
COMPONENT_VERSION=	1.5.0
COMPONENT_SUMMARY=	Cronie contains the standard UNIX daemon crond that runs specified programs at scheduled times and related tools.
COMPONENT_PROJECT_URL=	https://fedorahosted.org/cronie/wiki
COMPONENT_FMRI=		system/crond
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://fedorahosted.org/releases/c/r/cronie/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:9cf0e3f4f5042a9c09413d62c8e0c055e12401f70b112465f0f81f2c84ebfb3f
COMPONENT_LICENSE=	ISC, BSD, GPLv2
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var
CONFIGURE_OPTIONS+= --enable-syscrontab
CONFIGURE_OPTIONS+= --enable-anacron

COMPONENT_PRE_CONFIGURE_ACTION= \
	(cd $(SOURCE_DIR) && autoreconf)

install-cron:
	$(MKDIR) $(PROTO_DIR)/var/spool/cron
	$(MKDIR) $(PROTO_DIR)/etc/cron.d
	$(MKDIR) $(PROTO_DIR)/etc/cron.hourly
	$(INSTALL) -m755 $(SOURCE_DIR)/contrib/0anacron $(PROTO_DIR)/etc/cron.hourly/0anacron

install-anacron:
	$(INSTALL) -m644 $(SOURCE_DIR)/contrib/anacrontab $(PROTO_DIR)/etc/anacrontab
	$(INSTALL) -m644 $(SOURCE_DIR)/contrib/0hourly $(PROTO_DIR)/etc/cron.d/0hourly
	$(MKDIR) $(PROTO_DIR)/var/spool/anacron
	$(TOUCH) $(PROTO_DIR)/var/spool/anacron/cron.daily
	$(TOUCH) $(PROTO_DIR)/var/spool/anacron/cron.weekly
	$(TOUCH) $(PROTO_DIR)/var/spool/anacron/cron.monthly


build:		$(BUILD_32)

install:	$(INSTALL_32) install-cron install-anacron

test:		$(TEST_32)

REQUIRED_PACKAGES += system/library
