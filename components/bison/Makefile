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
BUILD_BITS= 64_and_32
# for the tests
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		bison
COMPONENT_VERSION=	3.0.4
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a72428c7917bdf9fa93cb8181c971b6e22834125848cf1d03ce10b1bb0716fe1
COMPONENT_ANITYA_ID=	193

TPNO=			24440

TEST_TARGET= $(TEST_64)
# we need to first generate the test suite
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_LIBDIR.32 =   $(GNULIB)
CONFIGURE_LIBDIR.64 =   $(GNULIB)/$(MACH64)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=		M4="/usr/gnu/bin/m4"
CONFIGURE_OPTIONS  += 		--disable-silent-rules

# the shared library we create needs to be built pic
COMPONENT_BUILD_ARGS += CC_PIC="$(CC_PIC)"

# this is cheesy but the tests don't seem to
# get compiled with the CFLAGS we built bison
# with, so they are 32-bit otherwise.
CONFIGURE_OPTIONS  +=		WARN_CXXFLAGS_TEST="$(CFLAGS)"

CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# the test suite actually generates a script
# that runs the just-built bison against the
# just-built files. to make it run the system
# one, we can just replace that script with
# a simpler one
COMPONENT_PRE_SYSTEM_TEST_ACTION= \
    (cd $(@D)/tests; mv bison bison.orig; \
        echo "\#!/bin/bash" > bison; \
        echo "IFS=" >> bison; \
        echo "exec /usr/bin/bison \$$@" >> bison; \
        chmod +x bison; \
    )

COMPONENT_POST_SYSTEM_TEST_ACTION= \
    (cd $(@D)/tests; rm -f bison; mv bison.orig bison)

# Strip compilation lines from test output
# and strange backslash lines. and random output,
# including rm complaints over nfs
COMPONENT_TEST_TRANSFORMS += \
    '-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*$(CXX).*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^config.status: .*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Nothing to be done for.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: .*is up to date.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^mv -f.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.$$|XXX_CC_XXX|g" ' \
    '-e "s|^updating examples.*$$|XXX_CC_XXX|g" ' \
    '-e "s|.*build-aux/ylwrap.*$$|XXX_CC_XXX|g" ' \
    '-e "s|.*examples/calc++/calc++-parser.stamp.*$$|XXX_CC_XXX|g" ' \
    '-e "s|.*tests/bison -o y.tab.c.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^rm:.*directory renamed.*$$|XXX_CC_XXX|g" ' \
    '-e "/^XXX_CC_XXX$$/d" '

REQUIRED_PACKAGES += developer/macro/gnu-m4
