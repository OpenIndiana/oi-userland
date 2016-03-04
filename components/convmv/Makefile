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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		convmv
COMPONENT_VERSION=	2.0
COMPONENT_PROJECT_URL=	http://www.j3e.de/linux/convmv/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:170cf675be1fca77868ff472e9340ca828b1463865a63d4f4b7b3bf4053db93f
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/convmv

TPNO=			27095

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

# Version of Perl to use in the convmv script.
PERL_VERSION =	5.20

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/ in [0-9][0-9]*\.*[0-9]* seconds.//" ' \
	'-e "/^unimplemented function: utime.*$$/d" '

COMPONENT_TEST_TARGETS=		test
COMPONENT_SYSTEM_TEST_TARGETS=	test
COMPONENT_SYSTEM_TEST_ENV=	CONVMV=/usr/bin/convmv

# Adjust the '#!/usr/bin/perl' at the beginning of the convmv script to use
# '#!/usr/perl5/$(PERL_VERSION)/bin/perl'
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i -e 's?/usr/bin/perl?/usr/perl5/$(PERL_VERSION)/bin/perl?' \
		$(PROTOUSRBINDIR)/convmv;

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TEST_64)

REQUIRED_PACKAGES += runtime/perl-520
