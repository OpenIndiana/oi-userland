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
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Crypt-DES
COMPONENT_VERSION =	2.7
HUMAN_VERSION=		2.07
COMPONENT_FMRI=		library/perl-5/crypt-des
COMPONENT_SUMMARY=	Crypt::DES - Perl DES encryption module
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Crypt::DES
COMPONENT_ARCHIVE_HASH=	\
    sha256:2db1ebb5837b4cb20051c0ee5b733b4453e3137df0a92306034c867621edd7e7
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/D/DP/DPARIS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Custom

include $(WS_MAKE_RULES)/common.mk

# filter out timing information
COMPONENT_TEST_TRANSFORMS += '-e "s/ *[0-9]* wallclock.*//"'
# filter out lines that could vary between runs
COMPONENT_TEST_TRANSFORMS += '-e "1,/^PERL_DL_NONLAZY/d"'

# Test results for this component omits the expected 'test_harness' pattern so add it
COMPONENT_POST_TEST_ACTION += \
	$(MV) $(COMPONENT_TEST_OUTPUT) $(COMPONENT_TEST_OUTPUT)-orig ; \
	echo "\ntest_harness" > $(COMPONENT_TEST_OUTPUT) ; \
	$(CAT) $(COMPONENT_TEST_OUTPUT)-orig >> $(COMPONENT_TEST_OUTPUT) ; \
	$(RM) $(COMPONENT_TEST_OUTPUT)-orig ;

# Manually added dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/crypt-cbc

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += system/library
