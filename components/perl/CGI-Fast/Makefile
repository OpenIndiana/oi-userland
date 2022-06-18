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
# Copyright 2022 Friedrich Kink
#

BUILD_STYLE = makemaker
BUILD_BITS = 32_and_64
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			CGI-Fast
COMPONENT_VERSION=		2.16
COMPONENT_FMRI=			library/perl-5/cgi-fast
COMPONENT_SUMMARY=		CGI::Fast - CGI Interface for Fast CGI
COMPONENT_CLASSIFICATION=	Development/Perl
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=		https://metacpan.org/pod/CGI::Fast
COMPONENT_ARCHIVE_HASH=		sha256:0223d7f91b80037b9dff5f37360640b71f5dc8dbd989a0593d5d22f3f73cb3d4
COMPONENT_ARCHIVE_URL=		https://cpan.metacpan.org/authors/id/L/LE/LEEJO/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Artistic
COMPONENT_LICENSE_FILE=		Artistic.txt

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TRANSFORMS += \
        '-e "/^\#/d"' \
        '-e "/^PERL/d"' \
        '-e "/^make/d"'

PERL_REQUIRED_PACKAGES += library/perl-5/cgi
PERL_REQUIRED_PACKAGES += library/perl-5/fcgi

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
