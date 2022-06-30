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

COMPONENT_NAME =		Mozilla-CA
HUMAN_VERSION =			20211001
COMPONENT_VERSION =		2021.10.1
COMPONENT_FMRI =		library/perl-5/mozilla-ca
COMPONENT_SUMMARY =		Mozilla::CA - Mozilla's CA cert bundle in PEM format
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Mozilla::CA
COMPONENT_ARCHIVE_HASH =	\
	sha256:122c8900000a9d388aa8e44f911cab6c118fe8497417917a84a8ec183971b449
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/A/AB/ABH/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		MPL v2.0

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
