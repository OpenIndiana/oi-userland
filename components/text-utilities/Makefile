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
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		text-utilities
COMPONENT_VERSION=	2.25.2
COMPONENT_PROJECT_URL=	https://www.kernel.org/pub/linux/utils/util-linux
COMPONENT_SRC=		util-linux-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e0457f715b73f4a349e1acb08cb410bf0edc9a74a3f75c357070f31f70e33cd6
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/v2.25/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/text-utilities

TPNO=			21750

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# We currently only want some of the text-utils text utilities from this
# component, so enumerate it in a macro that we can use for build and install.
# Anything else that we want should be added to this macro in the future.
PROGRAMS =	colcrt colrm column hexdump rev tailf

# Build a utility program used by one of the hexdump tests.
PROGRAMS +=	test_sysinfo

# Limit translations to the text utilities (and lib/* and include/* ) only.
COMPONENT_PRE_INSTALL_ACTION = \
	(cd $(@D)/po ; $(GMAKE) text-utilities.pot-update)

CONFIGURE_OPTIONS +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=		--bindir=$(CONFIGURE_BINDIR.32)

# We don't need the Python bindings built.
CONFIGURE_OPTIONS +=		--without-python

# Makefile incorrectly includes gcc(1) '-fsigned-char' in AM_CFLAGS, so we
# override it.
COMPONENT_BUILD_ARGS +=		AM_CFLAGS=""

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=		V=1

# Only build the programs that we want.
COMPONENT_BUILD_ARGS +=		bin_PROGRAMS="$(PROGRAMS)"
COMPONENT_BUILD_TARGETS =	$(PROGRAMS)

# Only install the bits we want.
COMPONENT_INSTALL_ARGS +=	bin_PROGRAMS="$(PROGRAMS)"
COMPONENT_INSTALL_TARGETS =	install-man install-binPROGRAMS

# Install the message files.
COMPONENT_POST_INSTALL_ACTION = \
	(cd $(@D)/po ; $(GMAKE) $(COMPONENT_INSTALL_ARGS) install)

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_TEST_ENV +=	TS_CMD_COLRM=$(PROTO_DIR)/usr/bin/colrm
COMPONENT_TEST_ENV +=	TS_CMD_COLUMN=$(PROTO_DIR)/usr/bin/column
COMPONENT_TEST_ENV +=	TS_CMD_HEXDUMP=$(PROTO_DIR)/usr/bin/hexdump
COMPONENT_TEST_ENV +=	TS_CMD_TAILF=$(PROTO_DIR)/usr/bin/tailf
COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"
COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/tests

# The hexdump tests expect the test_sysinfo program in a different location
# than where it's built.
COMPONENT_PRE_TEST_ACTION = $(CP) $(@D)/test_sysinfo $(COMPONENT_SRC)/

COMPONENT_TEST_CMD =		./run.sh
COMPONENT_TEST_ARGS =		--verbose
COMPONENT_TEST_TARGETS =	colrm column hexdump tailf

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH)-64.master

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		install $(TEST_64)


REQUIRED_PACKAGES += system/library
