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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2022 TIm Mooney.  All rights reserved.
#

#
# Note that package library/perl-5/xml-parser cannot use versionless
# packaging because this package migrated from the desktop consolidation
# with an incorrect version number.
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		XML-Parser
COMPONENT_VERSION=	2.44
COMPONENT_REVISION=	3
COMPONENT_FMRI=		library/perl-5/xml-parser
COMPONENT_SUMMARY=	XML::Parser - A perl module for parsing XML documents
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/XML::Parser
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1ae9d07ee9c35326b3d9aad56eae71a6730a73a116b9fe9e8a4758b7cc033216
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/T/TO/TODDR/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	xml-parser.license

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

# Enable ASLR for this component
#ASLR_MODE = $(ASLR_ENABLE)

# man pages go in the common area
COMPONENT_INSTALL_ENV += INSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

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

# runtime dependency on LWP::UserAgent (from libwww-perl) needed for the
# test suite
REQUIRED_PACKAGES += library/perl-5/libwww-perl-522
REQUIRED_PACKAGES += library/perl-5/libwww-perl-524
REQUIRED_PACKAGES += library/perl-5/libwww-perl-534

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += system/library
