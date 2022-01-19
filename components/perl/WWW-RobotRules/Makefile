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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2014, Alexander Pyhalov. All rights reserved.
# Copyright (c) 2022 Tim Mooney.  All rights reserved.
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		WWW-RobotRules
COMPONENT_VERSION=	6.02
IPS_COMPONENT_VERSION=	6.2
COMPONENT_REVISION=	2
COMPONENT_FMRI=		library/perl-5/www-robotrules
COMPONENT_SUMMARY=	WWW::RobotRules - database of robots.txt-derived permissions
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/WWW::RobotRules
COMPONENT_ARCHIVE_HASH=	\
    sha256:46b502e7a288d559429891eeb5d979461dd3ecc6a5c491ead85d165b6e03a51e
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/G/GA/GAAS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Artistic

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

# to run the test suite, we need the runtime dependency module URI
REQUIRED_PACKAGES += library/perl-5/uri-522
REQUIRED_PACKAGES += library/perl-5/uri-524
REQUIRED_PACKAGES += library/perl-5/uri-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
