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

BUILD_STYLE=modulebuild
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		HTML-Tree
COMPONENT_VERSION=	5.7
COMPONENT_HUMAN=	5.07
COMPONENT_FMRI=		library/perl-5/html-tree
COMPONENT_SUMMARY=	HTML::Tree - build and scan parse-trees of HTML
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_HUMAN)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/HTML::Tree
COMPONENT_ARCHIVE_HASH=	sha256:f0374db84731c204b86c1d5b90975fef0d30a86bd9def919343e554e31a9dbbf
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/K/KE/KENTNL/$(COMPONENT_ARCHIVE)
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
	'-e "s/,  *[0-9]* wallclock.*//"'

# runtime requirements HTML::Tagset needed to run the test suite
# HTML::Parser and Try::Tiny is recommended, so include it too
REQUIRED_PACKAGES += library/perl-5/try-tiny-522
REQUIRED_PACKAGES += library/perl-5/try-tiny-524
REQUIRED_PACKAGES += library/perl-5/try-tiny-534
REQUIRED_PACKAGES += library/perl-5/module-build-522
REQUIRED_PACKAGES += library/perl-5/module-build-524
REQUIRED_PACKAGES += library/perl-5/module-build-534
REQUIRED_PACKAGES += library/perl-5/html-tagset-522
REQUIRED_PACKAGES += library/perl-5/html-tagset-524
REQUIRED_PACKAGES += library/perl-5/html-tagset-534
REQUIRED_PACKAGES += library/perl-5/html-parser-522
REQUIRED_PACKAGES += library/perl-5/html-parser-524
REQUIRED_PACKAGES += library/perl-5/html-parser-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
