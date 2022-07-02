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

COMPONENT_NAME=		Email-Valid
COMPONENT_VERSION=	1.203
COMPONENT_FMRI=		library/perl-5/email-valid
COMPONENT_SUMMARY=	Email::Valid - Check validity of Internet email addresses
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Email::Valid
COMPONENT_ARCHIVE_HASH=	sha256:2021bfbb1e2c279e5ebd84680e596f97344d429850b232267b76f49037522b93
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/R/RJ/RJBS/$(COMPONENT_ARCHIVE)
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

# runtime requirements 
REQUIRED_PACKAGES += library/perl-5/net-domain-tld-522
REQUIRED_PACKAGES += library/perl-5/net-domain-tld-524
REQUIRED_PACKAGES += library/perl-5/net-domain-tld-534
REQUIRED_PACKAGES += library/perl-5/mailtools-522
REQUIRED_PACKAGES += library/perl-5/mailtools-524
REQUIRED_PACKAGES += library/perl-5/mailtools-534
REQUIRED_PACKAGES += library/perl-5/net-dns-522
REQUIRED_PACKAGES += library/perl-5/net-dns-524
REQUIRED_PACKAGES += library/perl-5/net-dns-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
