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

BUILD_STYLE = modulebuild
BUILD_BITS = 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Params-Validate
COMPONENT_VERSION =		1.30
COMPONENT_FMRI =		library/perl-5/params-validate
COMPONENT_SUMMARY =		Params::Validate - Validate method/function parameters
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Params::Validate
COMPONENT_ARCHIVE_HASH =	\
	sha256:9a3a35583d3125d07e8c802c1f92f5be7d526e76dd496e944da270b1e273d812
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DR/DROLSKY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# Test results for this component omits the expected 'test_harness' pattern so add it
COMPONENT_POST_TEST_ACTION += \
	$(MV) $(COMPONENT_TEST_OUTPUT) $(COMPONENT_TEST_OUTPUT)-orig ; \
	echo "\ntest_harness" > $(COMPONENT_TEST_OUTPUT) ; \
	$(CAT) $(COMPONENT_TEST_OUTPUT)-orig >> $(COMPONENT_TEST_OUTPUT) ; \
	$(RM) $(COMPONENT_TEST_OUTPUT)-orig ;

PERL_REQUIRED_PACKAGES += library/perl-5/module-build
PERL_REQUIRED_PACKAGES += library/perl-5/module-implementation
PERL_REQUIRED_PACKAGES += library/perl-5/test-fatal
PERL_REQUIRED_PACKAGES += library/perl-5/test-requires

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
