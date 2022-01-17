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
# Copyright (c) 2022 Tim Mooney.  All rights reserved.
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		XML-Simple
COMPONENT_VERSION=	2.22
COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/xml-simple
COMPONENT_SUMMARY=	XML::Simple - Easy API to maintain XML (esp config files)
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/XML::Simple
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b9450ef22ea9644ae5d6ada086dc4300fa105be050a2030ebd4efd28c198eb49
COMPONENT_ARCHIVE_URL=	\
    https://cpan.metacpan.org/authors/id/G/GR/GRANTM/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	xml-simple.license

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

# man pages go in the common area
COMPONENT_INSTALL_ENV += INSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

#
# use the same results for comparison for all builds
#
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

#
# filter out all output up to and including the test_harness line
# filter out timing information and anything else that varies between builds
# also remove all the module version display in the test output
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"' \
	'-e "/^\#/d"'

#
# XML::Simple can use either XML::Parser (which it doesn't list as a
# requirement) or XML::SAX, with or without XML::SAX::Expat (which it
# does list as a requirement, but which we don't currently ship).
# The listed build dependencies are (currently) enough for all the
# tests to pass.
#
REQUIRED_PACKAGES += library/perl-5/xml-namespacesupport-522
REQUIRED_PACKAGES += library/perl-5/xml-namespacesupport-524
REQUIRED_PACKAGES += library/perl-5/xml-namespacesupport-534
REQUIRED_PACKAGES += library/perl-5/xml-parser-522
REQUIRED_PACKAGES += library/perl-5/xml-parser-524
REQUIRED_PACKAGES += library/perl-5/xml-parser-534
REQUIRED_PACKAGES += library/perl-5/xml-sax-522
REQUIRED_PACKAGES += library/perl-5/xml-sax-524
REQUIRED_PACKAGES += library/perl-5/xml-sax-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
