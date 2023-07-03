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
COMPONENT_REVISION =		3
COMPONENT_SUMMARY =		Perl - Highly capable, feature-rich programming language
COMPONENT_PROJECT_URL =		https://www.perl.org/
COMPONENT_FMRI =		runtime/perl
COMPONENT_CLASSIFICATION =	Development/Perl

SINGLE_PERL_VERSION = no

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PERLVER=$(PERL_VERSION)
PKG_MACROS += PLV=$(shell echo $(PERL_VERSION) | tr -d .)

ifeq ($(PERL_VERSION),$(lastword $(PERL_VERSIONS)))
PKG_MACROS += VENDOR_MEDIATOR=\#
else
PKG_MACROS += VENDOR_MEDIATOR=
endif

# Auto-generated dependencies
