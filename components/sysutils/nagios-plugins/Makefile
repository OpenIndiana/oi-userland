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
# Copyright 2023 Marcel Telka
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nagios-plugins
COMPONENT_VERSION =		2.4.4
COMPONENT_SUMMARY =		Nagios Plugins
COMPONENT_PROJECT_URL =		https://github.com/nagios-plugins/nagios-plugins
COMPONENT_FMRI =		system/management/nagios/plugins
COMPONENT_CLASSIFICATION =	System/Enterprise Management
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL =		\
	$(COMPONENT_PROJECT_URL)/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	\
	sha256:9eb151c0665b4a9b8fbe0baf95656312e1c830fb1de7fa58aed358972b51c25d
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/common.mk

# force needed rpath
LD_OPTIONS += -R$(PG_LIBDIR)
LD_OPTIONS += -R$(MYSQL_LIBDIR)

CONFIGURE_OPTIONS +=	--enable-libtap
CONFIGURE_OPTIONS +=	--with-pgsql=$(PG_HOME)
CONFIGURE_OPTIONS +=	--with-mysql=$(MYSQL_HOME)
CONFIGURE_OPTIONS +=	--without-dbi
CONFIGURE_OPTIONS +=	--without-radius
CONFIGURE_OPTIONS +=	--without-smbclient-command
CONFIGURE_OPTIONS +=	--without-qmail-qstat-command
CONFIGURE_OPTIONS +=	--without-smtpctl-command

# Testing needs internet access and site specific setup
COMPONENT_TEST_TARGETS = test

# Manually added dependencies
TEST_REQUIRED_PACKAGES += diagnostic/fping
TEST_REQUIRED_PACKAGES += library/perl-5/crypt-x509
TEST_REQUIRED_PACKAGES += library/perl-5/libwww-perl
TEST_REQUIRED_PACKAGES += library/perl-5/text-glob
TEST_REQUIRED_PACKAGES += library/perl-5/timedate

# Auto-generated dependencies
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
