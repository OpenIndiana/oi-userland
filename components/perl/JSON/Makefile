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
# Copyright (c) 2022 Friedrich Kink.  All rights reserved.
#

BUILD_STYLE = makemaker
BUILD_BITS = 32_and_64
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		JSON
HUMAN_VERSION =			4.06
COMPONENT_VERSION =		4.6
COMPONENT_FMRI =		library/perl-5/json
COMPONENT_SUMMARY =		JSON - JSON (JavaScript Object Notation) encoder/decoder
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=		https://metacpan.org/pod/JSON
COMPONENT_ARCHIVE_HASH =	\
	sha256:1137e98a42208d802f3ad94a10855606c0455ddad167ba018557d751f6f7672e
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/I/IS/ISHIGAKI/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/test-pod

# Auto-generated dependencies
