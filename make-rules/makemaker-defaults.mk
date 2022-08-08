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

# Component defaults
COMPONENT_VERSION ?=		$(shell $(WS_TOOLS)/perl-version-convert $(COMPONENT_NAME) $(HUMAN_VERSION))
COMPONENT_CLASSIFICATION ?=	Development/Perl
COMPONENT_SRC ?=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE ?=		$(COMPONENT_SRC).tar.gz
COMPONENT_FMRI ?=		library/perl-5/$(shell echo $(COMPONENT_NAME) | tr [A-Z]_ [a-z]-)
ifneq ($(strip $(COMPONENT_PERL_MODULE)),)
COMPONENT_PERL_DISTRIBUTION ?=	$(subst ::,-,$(COMPONENT_PERL_MODULE))
COMPONENT_PROJECT_URL ?=	https://metacpan.org/pod/$(COMPONENT_PERL_MODULE)
endif
ifneq ($(strip $(COMPONENT_PERL_DISTRIBUTION)),)
COMPONENT_NAME ?=		$(COMPONENT_PERL_DISTRIBUTION)
endif
ifneq ($(strip $(COMPONENT_CPAN_AUTHOR)),)
COMPONENT_CPAN_AUTHOR1 =	$(shell echo $(COMPONENT_CPAN_AUTHOR) | cut -c 1)
COMPONENT_CPAN_AUTHOR2 =	$(shell echo $(COMPONENT_CPAN_AUTHOR) | cut -c 1-2)
COMPONENT_CPAN_AUTHOR_URL =	$(COMPONENT_CPAN_AUTHOR1)/$(COMPONENT_CPAN_AUTHOR2)/$(COMPONENT_CPAN_AUTHOR)
COMPONENT_ARCHIVE_URL ?=	https://cpan.metacpan.org/authors/id/$(COMPONENT_CPAN_AUTHOR_URL)/$(COMPONENT_ARCHIVE)
endif
# Enable ASLR by default.  Component could disable ASLR by setting
# COMPONENT_ASLR to 'no'.
ifeq ($(strip $(COMPONENT_ASLR)),no)
ASLR_MODE = $(ASLR_DISABLE)
else
ASLR_MODE = $(ASLR_ENABLE)
endif
