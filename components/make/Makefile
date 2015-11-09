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

COMPONENT_NAME=		make
COMPONENT_VERSION=	4.1
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/make/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:0bc7613389650ee6a24554b52572a272f7356164fd2c4132b0bcf13123e4fca5
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/make/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-make

TPNO=			24441

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

CONFIGURE_BINDIR.64 =   $(CONFIGURE_PREFIX)/bin

CONFIGURE_OPTIONS  +=		--program-prefix=g
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		--without-guile

# force re-runs to be the same
COMPONENT_PRE_TEST_ACTION = \
    ($(TOUCH) $(SOURCE_DIR)/getloadavg.c)

COMPONENT_SYSTEM_TEST_TARGETS= system-test
system-test: \
    COMPONENT_TEST_MASTER = \
         $(COMPONENT_TEST_RESULTS_DIR)/system-results-64.master

# Strip compilation lines from test output
COMPONENT_TEST_TRANSFORMS += \
    '-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^1-minute.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*load average.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*Running tests for GNU make.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.==========.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^Clearing work.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^config.status: .*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
    '-e "/^XXX_CC_XXX$$/d" '


ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# the test suite needs to be configured first
system-test:	configure $(SYSTEM_TEST_64)


REQUIRED_PACKAGES += system/library
