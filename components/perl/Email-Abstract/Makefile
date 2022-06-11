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

COMPONENT_NAME =		Email-Abstract
HUMAN_VERSION =			3.009
COMPONENT_VERSION =		3.9
COMPONENT_FMRI =		library/perl-5/email-abstract
COMPONENT_SUMMARY =		Email::Abstract - unified interface to mail representations
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/Email::Abstract
COMPONENT_ARCHIVE_HASH =	\
	sha256:040b7292e22e54815e9e6dfcdbfac9d874741930a20744ff5b369147dde201fc
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/R/RJ/RJBS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

PERL_REQUIRED_PACKAGES += library/perl-5/email-simple
PERL_REQUIRED_PACKAGES += library/perl-5/module-pluggable
PERL_REQUIRED_PACKAGES += library/perl-5/mro-compat

# Auto-generated dependencies
