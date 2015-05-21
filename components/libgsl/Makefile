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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gsl
COMPONENT_VERSION=	1.16
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/gsl/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:73bc2f51b90d2a780e6d266d43e487b3dbd78945dd0b04b14ca5980fe28d2f53
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libgsl

TPNO=			21884

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# By default, tests in each GSL sub-directory are linked statically against
# a set of .la files. We don't deliver those in the GSL package, so we
# adjust all the tests to link against the dynamic GSL library instead.
COMPONENT_POST_UNPACK_ACTION = \
	(cd $(COMPONENT_SRC); \
	for f in `ls */Makefile.am` ; do \
	    $(GSED) -i -e \
		's|^test_LDADD.*$$|test_LDFLAGS = -L`pwd`/../.libs/ -R`pwd`/../.libs/\ntest_LDADD = -lgsl|' \
		$$f ; \
	done)

# Recreate configure and top-level Makefile to pickup libsunperf changes.
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; ACLOCAL=aclocal-1.11 AUTOMAKE=automake-1.11 autoreconf -f)

LDFLAGS += $(CC_BITS)
LDFLAGS += $(studio_PIC)
LDFLAGS += $(studio_OPT)
LDFLAGS += $(LD_Z_TEXT)
LDFLAGS += $(LD_Z_DEFS)
LDFLAGS += $(LD_DEF_LIBS)

STUDIO_LIBS_PATH.32 =	/usr/lib/studio
STUDIO_LIBS_PATH.64 =	/usr/lib/studio/64

LDFLAGS += -L$(STUDIO_LIBS_PATH.$(BITS)) -R$(STUDIO_LIBS_PATH.$(BITS)) \
		-lsunperf -lfsu -lmtsk -lpicl -lkstat

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"

CC += $(CC_BITS)

COMPONENT_TEST_ARGS =	-k -i

# Master test results are different not only between 32-bit and 64-bit, but
# also between x86 and SPARC (different # of tests run).
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH)-$(BITS).master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# There are known problems in libsunperf that are causing GSL test failures
# in Solaris 12 with Studio 12.4 just on the x86 platform:
# linalg: FAIL:   LQ_update m(5,3) [88]                             (32-bit)
# caused by 20914954 cblas_gemm differences between x86 and sparcv7
# linalg: FAIL:   cholesky_invert hilbert(4)                        (64-bit)
# caused by 20909151 cblas_dsymm differences between amd64 and sparcv9.
test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/openmp
REQUIRED_PACKAGES += system/library/sunperf
