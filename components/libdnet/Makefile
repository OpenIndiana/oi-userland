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

PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)

COMPONENT_NAME=		libdnet
COMPONENT_VERSION=	1.12
COMPONENT_PROJECT_URL=	http://code.google.com/p/libdnet/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:83b33039787cf99990e977cef7f18a5d5e7aaffc4505548a83d31bd3515eb026
COMPONENT_ARCHIVE_URL=	http://libdnet.googlecode.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libdnet 
COMPONENT_ANITYA_ID=	6308

TPNO=			9402

TEST_TARGET= install $(TEST_32_and_64)
SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

# Fix 64-bit linking done via compiler.
LDFLAGS += $(CC_BITS)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Needed to generate libraries with a .so extension.
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; libtoolize --automake --copy ; \
		aclocal -I config ; \
		autoheader ; \
		automake --add-missing --copy ; \
		autoconf)

# Remove Linux specific functionality.
CONFIGURE_OPTIONS += ac_cv_dnet_linux_pf_packet=no

CONFIGURE_OPTIONS +=	--with-check=/usr

# Currently only support for Python 2.7.
CONFIGURE_OPTIONS +=	--with-python

PKG_MACROS +=		MACHINE=$(shell uname -m)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

COMPONENT_TEST_DIR =	$(@D)/test/check

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

# Needed to build the test programs.
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	(cd $(@D)/src ; $(GMAKE) libdnet.la )

COMPONENT_SYSTEM_TEST_DIR =	$(@D)/test/check

# Get correct libdnet.so.1 from the proto area.
TEST_LIBPATH.32 =	$(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =	$(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

REQUIRED_PACKAGES += developer/test/check
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/ksh93
