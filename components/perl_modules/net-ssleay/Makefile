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

COMPONENT_NAME=		Net-SSLeay
COMPONENT_VERSION=	1.78
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	http://search.cpan.org/dist/Net-SSLeay/
COMPONENT_ARCHIVE_HASH=	\
    sha256:e7f56427602f897446013b84b9ff51b8e8ab4fce0bbd086c4e28c198a942ed53
COMPONENT_ARCHIVE_URL=	http://search.cpan.org/CPAN/authors/id/M/MI/MIKEM/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	perl-mod/net-ssleay
TPNO=			33013

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/makemaker.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# The component Makefile.PL file will ask some questions on whether we want
# to run external tests, to which we want to answer with "n".
COMPONENT_CONFIGURE_ENV += ; echo "n" |
# Test failures.  keep going
COMPONENT_TEST_ARGS = -k -i
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^[mM]ake/d" ' \
	'-e "/^PERL_DL_NONLAZY/d" ' \
	'-e "/ENCRYPTED/d" ' \
	'-e "/^Files/d" ' \
	'-e "/^Failed /d" ' \
	'-e "/61_threads-cb-crash/d" ' \
	'-e "/62_threads-ctx_new-deadlock/d" ' \
	'-e "/^Running /d" ' \
	'-e "/^chmod /d" ' \
	'-e "/^Use of uninitialized/d" '

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
