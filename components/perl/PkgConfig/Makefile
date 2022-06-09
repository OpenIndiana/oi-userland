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
# Copyright 2022 Marcel Telka
#

BUILD_STYLE = makemaker
BUILD_BITS = 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PkgConfig
HUMAN_VERSION =			0.25026
COMPONENT_VERSION =		0.25
COMPONENT_FMRI =		library/perl-5/pkgconfig
COMPONENT_SUMMARY =		PkgConfig - Pure-Perl Core-Only replacement for pkg-config
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/PkgConfig
COMPONENT_ARCHIVE_HASH =	\
	sha256:4dba5ed3c2d6a681b95c5ebf14b6a6995ce6991ae4719bad7f1aaf38e987c2a0
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/P/PL/PLICEASE/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Test results for this component omits the expected 'test_harness' pattern so add it
COMPONENT_POST_TEST_ACTION += \
	$(MV) $(COMPONENT_TEST_OUTPUT) $(COMPONENT_TEST_OUTPUT)-orig ; \
	echo "\ntest_harness" > $(COMPONENT_TEST_OUTPUT) ; \
	$(CAT) $(COMPONENT_TEST_OUTPUT)-orig >> $(COMPONENT_TEST_OUTPUT) ; \
	$(RM) $(COMPONENT_TEST_OUTPUT)-orig ;

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
