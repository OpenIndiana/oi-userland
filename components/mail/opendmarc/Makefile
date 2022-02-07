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
# Copyright 2022 Friedrich Kink
#

BUILD_BITS=		64 # for binaries or 32_and_64 for libraries

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         opendmarc
COMPONENT_VERSION=      1.4.2
COMPONENT_SUMMARY=      OpenDMARC is a free open source software implementation of the DMARC specification.
COMPONENT_DESCRIPTION=	The OpenDMARC project is a community effort to develop and maintain \
			an open source package for providing DMARC report generation and policy \
			enforcement services. It includes a library for handling DMARC record \
			parsing, a database schema and tools for aggregating and processing  \
			transaction history to produce DMARC reports, and a filter that ties it  \
			all together with an MTA using the milter protocol. \
			In simple terms, DMARC takes the results of ARC, SPF and DKIM checks, done \
			by either upstream filters, or SPF checks that opendmarc performs itself, \
			and uses these to make a ""pass or fail"" decision. A domain owner may put a \
			record in the DNS to determine what should happen to a failing record: No \
			negative action (typically for testing), message quarantining, or outright \
			rejection at SMTP acceptance time.
COMPONENT_PROJECT_URL=  https://github.com/trusteddomainproject/OpenDMARC
COMPONENT_FMRI=         mail/opendmarc
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=          OpenDMARC-master
COMPONENT_ARCHIVE=      master.zip
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/heads/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:18d4bf8ead4e78038065a66ecfeee57fbbae1af8dc79e3b5adc5de3ca664d5e9
COMPONENT_LICENSE=      Copyright (c) 2009, 2010, 2012, 2013, The Trusted Domain Project.
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH=			$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= ( cd $(SOURCE_DIR) && autoreconf -v -i )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc/mail \
			--enable-static=no \
			--with-spf \
			--with-spf2-include=/usr/include \
			--with-spf2-lib=/usr/lib \
			--with-installdir=/usr

unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-64.master

COMPONENT_TEST_TRANSFORMS += " -n " \
	"-e '/TOTAL: /p' " \
	"-e '/PASS: /p' " \
	"-e '/SKIP: /p' " \
	"-e '/XFAIL: /p' " \
	"-e '/FAIL: /p' " \
	"-e '/XPASS: /p' " \
	"-e '/ERROR: /p' " \
	"-e '/^=======/p' "

# manually added
REQUIRED_PACKAGES += library/libspf2
# Auto-generated dependencies
REQUIRED_PACKAGES += library/libmilter
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
