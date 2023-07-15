#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2010, 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2021, Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ntp
HUMAN_VERSION=		4.2.8p17
COMPONENT_REVISION=	1
COMPONENT_VERSION=	$(subst p,.,$(HUMAN_VERSION))
COMPONENT_SUMMARY=	Network Time Protocol Daemon v4
COMPONENT_DESCRIPTION=	Network Time Protocol v4, NTP Daemon and Utilities
COMPONENT_PROJECT_URL=	https://www.ntp.org/
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:103dd272e6a66c5b8df07dce5e9a02555fcd6f1397bdfb782237328e89d3a866
COMPONENT_ARCHIVE_URL=	https://archive.ntp.org/ntp4/ntp-4.2/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	service/network/ntp
COMPONENT_CLASSIFICATION=	System/Services
COMPONENT_LICENSE=	ntp license

PATCH_LEVEL = 0

ASLR_MODE= $(ASLR_ENABLE)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS=

COMPONENT_PREP_ACTION = ( cd $(@D) && PATH="$(PATH)" autoreconf --force --install )

CFLAGS += -D_XOPEN_SOURCE=600 -D__EXTENSIONS__

CONFIGURE_BINDIR = $(USRSBINDIR)
CONFIGURE_SBINDIR = $(USRSBINDIR)

CONFIGURE_OPTIONS +=	--with-binsubdir=sbin
CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBDIR)/inet
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)/inet
CONFIGURE_OPTIONS +=	--enable-getifaddrs
CONFIGURE_OPTIONS +=	--enable-all-clocks
CONFIGURE_OPTIONS +=	--enable-solarisprivs
CONFIGURE_OPTIONS +=	--enable-debugging
CONFIGURE_OPTIONS +=	--enable-debugg-timing
CONFIGURE_OPTIONS +=	--disable-optional-args
CONFIGURE_OPTIONS +=	--enable-parse-clocks
CONFIGURE_OPTIONS +=	--enable-ignore-dns-errors
# To avoid arc4random_addrandom error
#CONFIGURE_OPTIONS +=   --without-sntp
CONFIGURE_OPTIONS +=	--without-ntpsnmpd
CONFIGURE_OPTIONS +=	--with-crypto=openssl
CONFIGURE_OPTIONS +=	--with-openssl-incdir=$(OPENSSL_INCDIR)
CONFIGURE_OPTIONS +=	--with-openssl-libdir=$(OPENSSL_LIBDIR.64)
CONFIGURE_OPTIONS +=	--disable-problem-tests
# workaround for https://bugs.ntp.org/show_bug.cgi?id=3552
CONFIGURE_OPTIONS +=	--disable-signalled-io

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

COMPONENT_INSTALL_ENV += PATH=$(PATH.gnu)

# of the build and test and deleting the extra lines, it is easier to just
# cat together all of the logs. The test TEST_PROGNAME3 tests the system
# log facility, so we have to get rid of the output because the pid is
# different every time. Same for TEST_PROGNAME. We have to edit out the
# syslog format lines to get rid of the time and the pid. And the packet
# processing test uses the current time so it changes.
#
# In addition, we append the config.h file so we know if the configuration
# ever changes. We get rid of the version number which changes every time
# we upgrade and the system string and endian info which is different between
# intel and SPARC.

COMPONENT_TEST_CREATE_TRANSFORMS = \
	@if [ -e $(COMPONENT_TEST_MASTER) ]; \
	then \
		print "\#!/bin/sh" > $(COMPONENT_TEST_TRANSFORM_CMD); \
		print '$(FIND) $(BUILD_DIR_64) -name test-\*.log | sort |\\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print ' xargs cat  | grep -v TEST_PROGNAME | \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'grep -v unsync |  \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'grep -v no-leap |  \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'grep -v add-leap |  \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'grep -v del-leap |  \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'sed -e "s/4.2..p[0-9]*//" | \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'sed -e "s/^.*\[[0-9]*\]: //" | \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'grep -v ^resp | grep -v ^sent \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print '> $(COMPONENT_TEST_SNAPSHOT)' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'cat $(BUILD_DIR_64)/config.h | \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'grep -v ENDIAN | grep -v STR_SYSTEM | \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print 'grep -v VERSION | grep -v PACKAGE_STRING \\' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
		print '>> $(COMPONENT_TEST_SNAPSHOT)' \
		    >> $(COMPONENT_TEST_TRANSFORM_CMD); \
	else \
		print 'Cannot find $(COMPONENT_TEST_MASTER)'; \
		exit 2; \
	fi

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
