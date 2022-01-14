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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2022 Tim Mooney.  All rights reserved.
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Authen-PAM
COMPONENT_VERSION=	16
COMPONENT_REVISION=	5
COMPONENT_FMRI=		library/perl-5/authen-pam
COMPONENT_SUMMARY=	Authen::PAM - Perl interface to PAM library
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Authen::PAM
COMPONENT_SRC=		$(COMPONENT_NAME)-0.16
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0e949bd9a2a9df0f829971030fe9169cbaf6cec78b92faf22f547ff6c6155c9b
COMPONENT_ARCHIVE_URL=	\
    https://cpan.metacpan.org/authors/id/N/NI/NIKIP/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	authen-pam.license

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

# the tests all pass, but can't all be run non-interactively
TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# man pages go in the common area
COMPONENT_INSTALL_ENV += INSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoconf )

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += system/library
