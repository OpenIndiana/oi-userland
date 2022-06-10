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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Exception-Class
COMPONENT_VERSION =		1.45
COMPONENT_FMRI =		library/perl-5/exception-class
COMPONENT_SUMMARY =		Exception::Class - A module that allows you to declare real exception classes in Perl
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Exception::Class
COMPONENT_ARCHIVE_HASH =	\
	sha256:5482a77ef027ca1f9f39e1f48c558356e954936fc8fbbdee6c811c512701b249
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/D/DR/DROLSKY/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += library/perl-5/class-data-inheritable
REQUIRED_PACKAGES += library/perl-5/devel-stacktrace

# Auto-generated dependencies
