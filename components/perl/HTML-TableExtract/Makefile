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
# Copyright (c) 2022 Friedrich Kink.  All rights reserved.
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		HTML-TableExtract
COMPONENT_VERSION=	2.15
COMPONENT_FMRI=		library/perl-5/html-tableextract
COMPONENT_SUMMARY=	HTML::TableExtract - Perl module for extracting the content contained in tables within an HTML document, either as text or encoded element trees.
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/HTML::TableExtract
COMPONENT_ARCHIVE_HASH=	sha256:86c59c9d58da3ca174da5e62f5a0fb02f4da02b1b1e01df9e5d14bb65e4c3ecf
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/M/MS/MSISK/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	LICENSE

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

#
# filter out all output up to and including the test_harness line
# filter out timing information and anything else that varies between builds
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^make/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"'

# runtime requirements HTML::Tree and HTML::Parser
REQUIRED_PACKAGES += library/perl-5/html-tree-522
REQUIRED_PACKAGES += library/perl-5/html-tree-524
REQUIRED_PACKAGES += library/perl-5/html-tree-534
REQUIRED_PACKAGES += library/perl-5/html-parser-522
REQUIRED_PACKAGES += library/perl-5/html-parser-524
REQUIRED_PACKAGES += library/perl-5/html-parser-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
