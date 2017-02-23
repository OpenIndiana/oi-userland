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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		DBI
COMPONENT_VERSION=	1.636
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8f7ddce97c04b4b7a000e65e5d05f679c964d62c8b02c94c1a7d815bb2dd676c
COMPONENT_ARCHIVE_URL=	http://backpan.perl.org/authors/id/T/TI/TIMB/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://search.cpan.org/~timb/DBI/
COMPONENT_BUGDB=	perl-mod/dbi
COMPONENT_ANITYA_ID=	2811

TPNO=			28024	

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/makemaker.mk

COMPONENT_TEST_ARGS = -k -i
COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^[mM]ake/d" ' \
	'-e "/^Files/d" ' \
	'-e "/^PERL/d" ' \
	'-e "/^Running/d" ' \
	'-e "/^chmod/d" ' \
	'-e "/^connect /d" ' \
	'-e "/^Testing/d" ' \
	'-e "/NullP/d" ' \
	'-e "/^\# \-\-\- Perl/d" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += system/library
