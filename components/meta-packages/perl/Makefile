#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Marcel Telka
#

BUILD_STYLE = pkg

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		perl
COMPONENT_VERSION =		$(PERL_VERSION)
COMPONENT_REVISION =		0
COMPONENT_SUMMARY =		Perl - Highly capable, feature-rich programming language
COMPONENT_PROJECT_URL =		https://www.perl.org/
COMPONENT_FMRI =		runtime/perl
COMPONENT_CLASSIFICATION =	Development/Perl

# This needs to be done before the common.mk include because here we still do
# have the full list of Perl versions in PERL_VERSIONS.
ifeq ($(PERL_VERSION),$(lastword $(PERL_VERSIONS)))
PKG_MACROS += VERSION_SWITCH=\#
else
PKG_MACROS += VERSION_SWITCH=
endif

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
