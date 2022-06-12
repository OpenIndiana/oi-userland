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

COMPONENT_NAME =		XML-LibXML
HUMAN_VERSION =			2.0134
COMPONENT_VERSION =		2.1.34
COMPONENT_FMRI =		library/perl-5/xml-libxml
COMPONENT_SUMMARY =		XML::LibXML - Perl Binding for libxml2
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL =		https://metacpan.org/pod/XML::LibXML
COMPONENT_ARCHIVE_HASH =	\
	sha256:f0bca4d0c2da35d879fee4cd13f352014186cedab27ab5e191f39b5d7d4f46cf
COMPONENT_ARCHIVE_URL =		https://cpan.metacpan.org/authors/id/S/SH/SHLOMIF/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		Artistic

include $(WS_MAKE_RULES)/common.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

PERL_REQUIRED_PACKAGES += library/perl-5/xml-namespacesupport
PERL_REQUIRED_PACKAGES += library/perl-5/xml-sax
PERL_REQUIRED_PACKAGES += library/perl-5/xml-sax-base

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
