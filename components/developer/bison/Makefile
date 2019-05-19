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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bison
COMPONENT_VERSION=	3.4.1
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/bison/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SUMMARY=	bison - A YACC Replacement
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:27159ac5ebf736dffd5636fd2cd625767c9e437de65baa63cb0de83570bd820d
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/bison/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_FMRI=		developer/parser/bison

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Tests need this
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_LIBDIR.32 =   $(GNULIB)
CONFIGURE_LIBDIR.64 =   $(GNULIB)/$(MACH64)

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--disable-silent-rules
CONFIGURE_OPTIONS += 	--disable-dependency-tracking
CONFIGURE_OPTIONS +=	--disable-yacc

# the shared library we create needs to be built pic
COMPONENT_BUILD_ARGS += CC_PIC="$(CC_PIC)"

# this is cheesy but the tests don't seem to
# get compiled with the CFLAGS we built bison
# with, so they are 32-bit otherwise.
CONFIGURE_OPTIONS +=	WARN_CXXFLAGS_TEST="$(CFLAGS)"

CONFIGURE_ENV += 	M4="/usr/gnu/bin/m4"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

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
	'-e "/^rm /d" ' \
	'-e "/^touch /d" ' \
	'-e "/^XXX_CC_XXX$$/d" '

$(INSTALL_32):	$(INSTALL_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Two test suite cases utilitize Doxygen
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
# Auto-generated dependencies
REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/gnu-gettext
