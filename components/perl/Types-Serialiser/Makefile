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
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Types-Serialiser
HUMAN_VERSION =			1.01
COMPONENT_VERSION =		1.1
COMPONENT_FMRI =		library/perl-5/types-serialiser
COMPONENT_SUMMARY =		Types::Serialiser - simple data types for common serialisation formats
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Types::Serialiser
COMPONENT_ARCHIVE_HASH =	\
	sha256:f8c7173b0914d0e3d957282077b366f0c8c70256715eaef3298ff32b92388a80
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/M/ML/MLEHMANN/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/common-sense

# Auto-generated dependencies
