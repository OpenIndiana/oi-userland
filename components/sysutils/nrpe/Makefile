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
# Copyright 2022 Marcel Telka
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nrpe
COMPONENT_VERSION =		4.1.1
COMPONENT_SUMMARY =		Nagios Remote Plugin Executor
COMPONENT_PROJECT_URL =		https://github.com/NagiosEnterprises/nrpe
COMPONENT_FMRI =		system/management/nagios/nrpe
COMPONENT_CLASSIFICATION =	System/Enterprise Management
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL =		\
	https://github.com/NagiosEnterprises/nrpe/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	\
	sha256:0e716a7d904e0a441be52a0ef82c1138b949bad81c1da93056a81405aabcc0d7
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	LICENSE.md

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-install-method=os
CONFIGURE_OPTIONS += --enable-command-args
CONFIGURE_OPTIONS += --with-piddir=$(VARDIR)/run
CONFIGURE_OPTIONS += --with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-nrpe-user=nrpe
CONFIGURE_OPTIONS += --with-nrpe-group=nrpe

COMPONENT_BUILD_TARGETS = nrpe

COMPONENT_INSTALL_ARGS += NAGIOS_INSTALL_OPTS=
COMPONENT_INSTALL_ARGS += NRPE_INSTALL_OPTS=
# The default 'install' target installs both nrpe and check_nrpe.  Since we do
# not need check_nrpe for now we need to override it by 'install-daemon'
# target.
COMPONENT_INSTALL_TARGETS = install-daemon
COMPONENT_INSTALL_TARGETS += install-config
COMPONENT_INSTALL_TARGETS += install-init

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
