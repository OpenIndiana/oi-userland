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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		popt
COMPONENT_VERSION=	1.16
COMPONENT_PROJECT_URL=	http://freecode.com/projects/popt/
COMPONENT_ARCHIVE_HASH= \
    sha256:e728ed296fe9f069a0e005003c3d6b2dde3d9cad453422a10d6558616d304cc8
COMPONENT_ARCHIVE_URL=	https://launchpad.net/$(COMPONENT_NAME)/head/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/popt
COMPONENT_ANITYA_ID=	3689

TPNO=			27265

TEST_TARGET= install $(TEST_32_and_64)
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) ; $(TOUCH) config.rpath) ;

# Needed to get "gmake test" to work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Add /usr/gnu/bin at the front of $PATH for GNU gettext.
CONFIGURE_ENV +=	PATH=$(GNUBIN):$(PATH)

CONFIGURE_OPTIONS +=	--disable-nls

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Get correct libpopt.so.0 from the proto area.
TEST_LIBPATH.32 =       $(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =       $(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=   LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

# api-sanity-autotest.pl is part of the API Sanity Checker
# http://ispras.linuxbase.org/index.php/API_Sanity_Autotest
# (which we don't have in Solaris), so expect that test to fail.

COMPONENT_TEST_TRANSFORMS += \
	'-e "/Entering directory/d"' \
	'-e "/Leaving directory/d"' \
	'-e "/recursive/d"' \
	'-e "/check-local/d"' \
	'-e "/check-TESTS/d"' \
	'-e "/^Making/d"' \
	'-e "/^make/d"'
