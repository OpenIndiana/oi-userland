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

COMPONENT_NAME=		Sub-Exporter-Progressive
COMPONENT_VERSION =	0.1.13
HUMAN_VERSION=		0.001013
COMPONENT_FMRI=		library/perl-5/sub-exporter-progressive
COMPONENT_SUMMARY=	Sub::Exporter::Progressive - Only use Sub::Exporter if you need it
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Sub::Exporter::Progressive
COMPONENT_ARCHIVE_HASH=	\
    sha256:d535b7954d64da1ac1305b1fadf98202769e3599376854b2ced90c382beac056
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/F/FR/FREW/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv1, Artistic

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
