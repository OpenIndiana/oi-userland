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
BUILD_BITS= 64_and_32
# Built in SFW with gcc and builds cleanly now only with gcc
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		guile
COMPONENT_VERSION=	1.8.8
COMPONENT_ARCHIVE_HASH=	\
    sha256:c3471fed2e72e5b04ad133bbaaf16369e8360283679bcf19800bc1b381024050

TPNO=			28097

include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_ENV +=	CPPFLAGS="-I/usr/include/gmp -D__USE_LEGACY_PROTOTYPES__"
CONFIGURE_OPTIONS +=	--disable-static 
CONFIGURE_OPTIONS +=	--disable-error-on-warning
CONFIGURE_OPTIONS +=	ac_cv_type_complex_double=no

# Remove the GNU specific "-pthreads" Cflags option from the guile config
# files. In case we need to back-port this to earlier versions of Solaris,
# -D_POSIX_PTHREAD_SEMANTICS is added in its place, which makes the pthreads
# interfaces behave as specified in the POSIX standard (even though it does
# nothing for Solaris 12).

PROTOPKGCONFIGDIR.32 = $(PROTOPKGCONFIGDIR)
PROTOPKGCONFIGDIR.64 = $(PROTOPKGCONFIGDIR64)

COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i -e 's/-pthreads/-D_POSIX_PTHREAD_SEMANTICS/' \
		$(PROTOPKGCONFIGDIR.$(BITS))/guile-1.8.pc;

# We only deliver 64-bit binaries and in /usr/bin.
COMPONENT_POST_INSTALL_ACTION.32 += \
	$(GSED) -i -e 's|$(USRBINDIR)/$(MACH32)|$(USRBINDIR)|' \
		$(PROTOUSRBINDIR)/$(MACH32)/guile-config;

# Different test results on x86 and SPARC.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^Totals for this test run:/p" ' \
	'-e "/^passes:/p" ' \
	'-e "/^failures:/p" ' \
	'-e "/^unexpected passes:/p" ' \
	'-e "/^expected failures:/p" ' \
	'-e "/^unresolved test cases:/p" ' \
	'-e "/^untested test cases:/p" ' \
	'-e "/^unsupported test cases:/p" ' \
	'-e "/^errors:/p" ' \
	'-e "/^Running/p" ' \
	'-e "/^=======/p" ' \
	'-e "/^UNRESOLVED:/p" ' \
	'-e "/^PASS:/p" ' \
	'-e "/^FAIL:/p" ' \
	'-e "/failed/p" ' \
	'-e "/passed/p" '

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/gcc-3-runtime
REQUIRED_PACKAGES += system/library/gcc-45-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
