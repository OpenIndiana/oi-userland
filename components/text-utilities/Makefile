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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
COMPILER= gcc
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		text-utilities
COMPONENT_VERSION=	2.28
COMPONENT_PROJECT_URL=	https://www.kernel.org/pub/linux/utils/util-linux
COMPONENT_SRC=		util-linux-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:395847e2a18a2c317170f238892751e73a57104565344f8644090c8b091014bb
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TPNO=			29447

TEST_TARGET= install $(TEST_64)
SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

# We currently only want some of the text-utils text utilities from this
# component, so enumerate it in a macro that we can use for build and install.
# Anything else that we want should be added to this macro in the future.
PROGRAMS =	colcrt colrm column hexdump rev tailf

# Build a utility program used by one of the hexdump tests.
PROGRAMS +=	test_sysinfo

# Limit translations to the text utilities (and lib/* and include/* ) only.
COMPONENT_PRE_INSTALL_ACTION = \
	(cd $(@D)/po ; $(GMAKE) text-utilities.pot-update)

# We don't need the Python bindings built.
CONFIGURE_OPTIONS +=		--without-python

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

COMPONENT_TEST_ENV +=	TS_CMD_COLRM=$(PROTOUSRBINDIR)/colrm
COMPONENT_TEST_ENV +=	TS_CMD_COLUMN=$(PROTOUSRBINDIR)/column
COMPONENT_TEST_ENV +=	TS_CMD_HEXDUMP=$(PROTOUSRBINDIR)/hexdump
COMPONENT_TEST_ENV +=	TS_CMD_TAILF=$(PROTOUSRBINDIR)/tailf
COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"
COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/tests

# The hexdump tests expect the test_sysinfo program in a different location
# than where it's built.
COMPONENT_PRE_TEST_ACTION = $(CP) $(@D)/test_sysinfo $(COMPONENT_SRC)/

COMPONENT_TEST_CMD =		./run.sh
COMPONENT_TEST_ARGS =		--verbose
COMPONENT_TEST_TARGETS =	colrm column hexdump tailf

COMPONENT_SYSTEM_TEST_ENV +=   TS_CMD_COLRM=$(USRBINDIR)/colrm
COMPONENT_SYSTEM_TEST_ENV +=   TS_CMD_COLUMN=$(USRBINDIR)/column
COMPONENT_SYSTEM_TEST_ENV +=   TS_CMD_HEXDUMP=$(USRBINDIR)/hexdump
COMPONENT_SYSTEM_TEST_ENV +=   TS_CMD_TAILF=$(USRBINDIR)/tailf
COMPONENT_SYSTEM_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"
COMPONENT_SYSTEM_TEST_DIR =    $(COMPONENT_SRC)/tests

# Build the test_sysinfo program; copy it where the tests are looking for it.
COMPONENT_PRE_SYSTEM_TEST_ACTION = \
	(cd $(@D) ; $(GMAKE) AM_CFLAGS="" \
		V=1 bin_PROGRAMS="test_sysinfo" test_sysinfo ; \
		$(CP) test_sysinfo $(SOURCE_DIR))

COMPONENT_SYSTEM_TEST_CMD =	./run.sh
COMPONENT_SYSTEM_TEST_ARGS =	--verbose
COMPONENT_SYSTEM_TEST_TARGETS =	colrm column hexdump tailf
