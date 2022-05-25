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

COMPONENT_NAME =		Class-Singleton
COMPONENT_VERSION =		1.6
COMPONENT_FMRI =		library/perl-5/class-singleton
COMPONENT_SUMMARY =		Class::Singleton - Implementation of a "Singleton" class
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Class::Singleton
COMPONENT_ARCHIVE_HASH =	\
	sha256:27ba13f0d9512929166bbd8c9ef95d90d630fc80f0c9a1b7458891055e9282a4
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/S/SH/SHAY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
