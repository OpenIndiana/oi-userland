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

COMPONENT_NAME =		Params-Util
HUMAN_VERSION =			1.07
COMPONENT_VERSION =		1.7
COMPONENT_FMRI =		library/perl-5/params-util
COMPONENT_SUMMARY =		Params::Util - Simple, compact and correct param-checking functions
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Params::Util
COMPONENT_ARCHIVE_HASH =	\
	sha256:30f1ec3f2cf9ff66ae96f973333f23c5f558915bb6266881eac7423f52d7c76c
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/A/AD/ADAMK/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
