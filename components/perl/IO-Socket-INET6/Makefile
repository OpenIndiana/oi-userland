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

COMPONENT_NAME=		IO-Socket-INET6
COMPONENT_VERSION=	2.73
#COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/io-socket-inet6
COMPONENT_SUMMARY=	IO::Socket::INET6 - Object interface for AF_INET/AF_INET6 domain sockets
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/IO::Socket::INET6
COMPONENT_ARCHIVE_HASH=	\
    sha256:b6da746853253d5b4ac43191b4f69a4719595ee13a7ca676a8054cf36e6d16bb
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/S/SH/SHLOMIF/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2, Artistic

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
REQUIRED_PACKAGES += library/perl-5/socket6-522
REQUIRED_PACKAGES += library/perl-5/socket6-524
REQUIRED_PACKAGES += library/perl-5/socket6-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
