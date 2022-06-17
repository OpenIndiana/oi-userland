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

COMPONENT_NAME=		Test-Warnings
COMPONENT_VERSION =	0.31
HUMAN_VERSION=		0.031
COMPONENT_FMRI=		library/perl-5/test-warnings
COMPONENT_SUMMARY=	Test::Warnings - Test for warnings and the lack of them
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Test::Warnings
COMPONENT_ARCHIVE_HASH=	\
    sha256:1e542909fef305e45563e9878ea1c3b0c7cef1b28bb7ae07eba2e1efabec477b
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/E/ET/ETHER/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv1, Artistic

include $(WS_MAKE_RULES)/common.mk

# Part of the test output is randomly generated
COMPONENT_TEST_TRANSFORMS += '-e "s/\(Does::Not::Exist::\)[0-9]*/\1RANDOM/"'

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
