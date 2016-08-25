#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pmtools
COMPONENT_VERSION=	2.0.0
COMPONENT_PROJECT_URL=	http://search.cpan.org/dist/pmtools/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5863fc9434d6a8d7311fd612cf243c29c3573aaba9caa7a8fb54154089d8baf3
COMPONENT_ARCHIVE_URL=	http://search.cpan.org/CPAN/authors/id/M/ML/MLFISHER/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/perl-pmtools
TPNO=			31142

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/makemaker.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_ENV +=   PATH="/usr/perl5/$(PERLVER)/bin:$(PATH)"
COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/\s*[0-9][0-9]* wallclock secs (.*CPU)$$/ <TIMINGS REMOVED>/" ' \
	'-e "/^PERL_DL_NONLAZY/d" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += system/core-os
