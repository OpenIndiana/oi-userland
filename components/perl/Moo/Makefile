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

COMPONENT_NAME=		Moo
COMPONENT_VERSION =	2.5.4
HUMAN_VERSION=		2.005004
COMPONENT_FMRI=		library/perl-5/moo
COMPONENT_SUMMARY=	Moo - Minimalist Object Orientation (with Moose compatibility)
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Moo
COMPONENT_ARCHIVE_HASH=	\
    sha256:e3030b80bd554a66f6b3c27fd53b1b5909d12af05c4c11ece9a58f8d1e478928
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/H/HA/HAARG/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv1, Artistic

include $(WS_MAKE_RULES)/common.mk

# Manually added dependencies
REQUIRED_PACKAGES += library/perl-5/class-method-modifiers-522
REQUIRED_PACKAGES += library/perl-5/class-method-modifiers-524
REQUIRED_PACKAGES += library/perl-5/class-method-modifiers-534
REQUIRED_PACKAGES += library/perl-5/devel-globaldestruction-522
REQUIRED_PACKAGES += library/perl-5/devel-globaldestruction-524
REQUIRED_PACKAGES += library/perl-5/devel-globaldestruction-534
REQUIRED_PACKAGES += library/perl-5/import-into-522
REQUIRED_PACKAGES += library/perl-5/import-into-524
REQUIRED_PACKAGES += library/perl-5/import-into-534
REQUIRED_PACKAGES += library/perl-5/module-runtime-522
REQUIRED_PACKAGES += library/perl-5/module-runtime-524
REQUIRED_PACKAGES += library/perl-5/module-runtime-534
REQUIRED_PACKAGES += library/perl-5/role-tiny-522
REQUIRED_PACKAGES += library/perl-5/role-tiny-524
REQUIRED_PACKAGES += library/perl-5/role-tiny-534
REQUIRED_PACKAGES += library/perl-5/sub-quote-522
REQUIRED_PACKAGES += library/perl-5/sub-quote-524
REQUIRED_PACKAGES += library/perl-5/sub-quote-534
REQUIRED_PACKAGES += library/perl-5/test-fatal-522
REQUIRED_PACKAGES += library/perl-5/test-fatal-524
REQUIRED_PACKAGES += library/perl-5/test-fatal-534

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
