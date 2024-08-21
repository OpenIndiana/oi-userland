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
# This file was automatically generated using the following command:
#   $WS_TOOLS/perl-integrate-module Mozilla::PublicSuffix
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		Mozilla::PublicSuffix
HUMAN_VERSION =			1.0.7
COMPONENT_SUMMARY =		Mozilla::PublicSuffix - Get a domain name's public suffix via the Mozilla Public Suffix List
COMPONENT_CPAN_AUTHOR =		TOMHUKINS
COMPONENT_ARCHIVE_HASH =	\
	sha256:6815e292161ba8192b434398db295e229b3e61574e6a61994e90f359a2c71b21
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =			$(COMPONENT_NAME)-v$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION += \
	$(CP) $(COMPONENT_DIR)/files/public_suffix_list.dat $(SOURCE_DIR)/effective_tld_names.dat ;

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/module-build
PERL_REQUIRED_PACKAGES += library/perl-5/uri
PERL_REQUIRED_PACKAGES += runtime/perl
