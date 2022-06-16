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

BUILD_STYLE=modulebuild
BUILD_BITS=32_and_64
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Devel-CheckCompiler
COMPONENT_VERSION =	0.7
HUMAN_VERSION=		0.07
COMPONENT_FMRI=		library/perl-5/devel-checkcompiler
COMPONENT_SUMMARY=	Devel::CheckCompiler - Check the compiler's availability
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Devel::CheckCompiler
COMPONENT_ARCHIVE_HASH=	\
    sha256:768b7697b4b8d4d372c7507b65e9dd26aa4223f7100183bbb4d3af46d43869b5
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/S/SY/SYOHEX/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv1, Artistic

include $(WS_MAKE_RULES)/common.mk

# Test results for this component omits the expected 'test_harness' pattern so add it
COMPONENT_POST_TEST_ACTION += \
	$(MV) $(COMPONENT_TEST_OUTPUT) $(COMPONENT_TEST_OUTPUT)-orig ; \
	echo "\ntest_harness" > $(COMPONENT_TEST_OUTPUT) ; \
	$(CAT) $(COMPONENT_TEST_OUTPUT)-orig >> $(COMPONENT_TEST_OUTPUT) ; \
	$(RM) $(COMPONENT_TEST_OUTPUT)-orig ;

# Manually added dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/module-build-tiny

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
