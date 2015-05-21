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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

#
# Note that package library/perl-5/xml-parser cannot use versionless
# packaging because this package migrated from the desktop consolidation
# with an incorrect version number.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		XML-Parser
COMPONENT_VERSION=	2.41
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b48197cd2265a26c5f016489f11a7b450d8833cb8b3d6a46ee15975740894de9
COMPONENT_ARCHIVE_URL=	http://search.cpan.org/CPAN/authors/id/T/TO/TODDR/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://search.cpan.org/~toddr/
COMPONENT_BUGDB=	perl-mod/xml-parser

TPNO=			9386

# build threaded 5.12 support too
PERL_VERSIONS += 5.12-mt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/makemaker.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# man pages go in the common area
COMPONENT_INSTALL_ENV += INSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
        '-e "s|\(^Files=\).*|\1|" '

PKG_MACROS +=	PERL_A=$(shell arch)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += system/library
