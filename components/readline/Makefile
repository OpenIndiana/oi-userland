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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		readline
COMPONENT_VERSION=	5.2
COMPONENT_PROJECT_URL=	http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:12e88d96aee2cd1192500356f0535540db499282ca7f76339fb4228c31249f45
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/readline/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/readline

TPNO=			9042

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

LINT_FLAGS += -I$(PROTO_DIR)/usr/include

CC += $(CC_BITS)

# readline likes to use ld directly and this is the easiest
# way to get it to add -lc
LDFLAGS += -lc
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		LDFLAGS="$(LDFLAGS)"

# Build the readline examples as well.
COMPONENT_BUILD_TARGETS =	everything

COMPONENT_TEST_DIR =		$(@D)/examples
COMPONENT_TEST_CMD =		$(CAT) $(SOURCE_DIR)/examples/Inputrc | ./rlcat
COMPONENT_TEST_TARGETS =

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += system/library
