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
# Copyright 2022 Niklas Poslovski
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Net-SNMP
COMPONENT_VERSION=	6.0.1
#COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/net-snmp
COMPONENT_SUMMARY=	Net::SNMP - Object oriented interface to SNMP
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Net::SNMP
COMPONENT_ARCHIVE_HASH=	\
    sha256:14c37bc1cbb3f3cdc7d6c13e0f27a859f14cdcfd5ea54a0467a88bc259b0b741
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/D/DT/DTOWN/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv1, Artistic

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

#
# use the same results for comparison for all builds
#
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

#
# filter out all output up to and including the test_harness line
# filter out timing information and anything else that varies between builds
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"'

# Manually added dependencies
REQUIRED_PACKAGES += library/perl-5/digest-hmac-522
REQUIRED_PACKAGES += library/perl-5/digest-hmac-524
REQUIRED_PACKAGES += library/perl-5/digest-hmac-534
REQUIRED_PACKAGES += library/perl-5/digest-sha1-522
REQUIRED_PACKAGES += library/perl-5/digest-sha1-524
REQUIRED_PACKAGES += library/perl-5/digest-sha1-534
REQUIRED_PACKAGES += library/perl-5/crypt-des-522
REQUIRED_PACKAGES += library/perl-5/crypt-des-524
REQUIRED_PACKAGES += library/perl-5/crypt-des-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
