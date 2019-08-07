#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Andrzej Szeszo.  All rights reserved.
# Copyright 2016-2018 Aurelien Larcher. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gcc
COMPONENT_VERSION= 8.3.0
COMPONENT_MAJOR_VERSION=	$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\([0-9]\+\)\.[0-9]\+.*/\1/')
THIS_GCC_PKGVERSION= $(COMPONENT_VERSION)-OI-$(COMPONENT_REVISION)
COMPONENT_FMRI= developer/gcc-$(COMPONENT_MAJOR_VERSION)
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_SUMMARY= GNU Compiler Collection
MPFR_NAME= mpfr
MPFR_VERSION=4.0.2
MPC_NAME=mpc
MPC_VERSION=1.1.0
GMP_NAME=gmp
GMP_VERSION=6.1.2
COMPONENT_SUMMARY= GNU Compiler Collection
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:64baadfe6cc0f4947a84cb12d7f0dfaf45bb58b7e92461639596c21e02d97d2c
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnu.org/gnu/gcc/gcc-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gcc.gnu.org/
PATCH_EACH_ARCHIVE=1
PATCHDIR_PATCHES = $(shell find $(PATCH_DIR) $(PARFAIT_PATCH_DIR) -type f -name '$(PATCH_PATTERN)' \
                                2>/dev/null | sort) $(EXTRA_PATCHES)

COMPONENT_SRC_1=    $(MPFR_NAME)-$(MPFR_VERSION)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_URL_1= http://www.mpfr.org/$(COMPONENT_SRC_1)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= \
  sha256:c05e3f02d09e0e9019384cdd58e0f19c64e6db1fd6f5ecf77b4b1c61ca253acc
CLEAN_PATHS += $(COMPONENT_SRC_1)
COMPONENT_POST_UNPACK_ACTION_1 += ( $(RM) -r $(COMPONENT_SRC)/$(MPFR_NAME) && $(CP) -rpP $(COMPONENT_SRC_1) $(COMPONENT_SRC)/$(MPFR_NAME) )

COMPONENT_SRC_2= $(MPC_NAME)-$(MPC_VERSION)
COMPONENT_ARCHIVE_2= $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_URL_2=  https://ftp.gnu.org/gnu/mpc/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2= \
  sha256:6985c538143c1208dcb1ac42cedad6ff52e267b47e5f970183a3e75125b43c2e
CLEAN_PATHS += $(COMPONENT_SRC_2)
COMPONENT_POST_UNPACK_ACTION_2 += ( $(RM) -r $(COMPONENT_SRC)/$(MPC_NAME) && $(CP) -rpP $(COMPONENT_SRC_2) $(COMPONENT_SRC)/$(MPC_NAME) )

COMPONENT_SRC_3= $(GMP_NAME)-$(GMP_VERSION)
COMPONENT_ARCHIVE_3= $(COMPONENT_SRC_3).tar.bz2
COMPONENT_ARCHIVE_URL_3=  http://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE_3)
COMPONENT_ARCHIVE_HASH_3= \
  sha256:5275bb04f4863a13516b2f39392ac5e272f5e1bb8057b18aec1c9b79d73d8fb2
CLEAN_PATHS += $(COMPONENT_SRC_3)
COMPONENT_POST_UNPACK_ACTION_3 += ( $(RM) -r $(COMPONENT_SRC)/$(GMP_NAME) && $(CP) -rpP $(COMPONENT_SRC_3) $(COMPONENT_SRC)/$(GMP_NAME) )

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CPPFLAGS=
CFLAGS=
CXXFLAGS=

CONFIGURE_PREFIX= /usr/gcc/$(COMPONENT_MAJOR_VERSION)
PATH=$(PATH.gnu)

COMMON_ENV=  LD_OPTIONS="-zignore -zcombreloc -i"
COMMON_ENV+= LD_FOR_TARGET=/usr/bin/ld
COMMON_ENV+= LD_FOR_HOST=/usr/bin/ld
COMMON_ENV+= LD=/usr/bin/ld

CONFIGURE_ENV+= $(COMMON_ENV)
COMPONENT_BUILD_ENV+= $(COMMON_ENV)
COMPONENT_INSTALL_ENV+= $(COMMON_ENV)

CONFIGURE_OPTIONS+= --sbindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --host $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --build $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --target $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --with-pkgversion="OpenIndiana $(THIS_GCC_PKGVERSION)"
CONFIGURE_OPTIONS+= --with-bugurl="https://bugs.openindiana.org"
CONFIGURE_OPTIONS+= --enable-plugins
CONFIGURE_OPTIONS+= --enable-objc-gc
CONFIGURE_OPTIONS+= --enable-initfini-array
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,lto,objc
CONFIGURE_OPTIONS+= --without-gnu-ld
CONFIGURE_OPTIONS+= --with-ld=/usr/bin/ld
CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/$(GNU_TRIPLET)/bin
CONFIGURE_OPTIONS+= --disable-libitm
CONFIGURE_OPTIONS+= enable_frame_pointer=yes

# On SPARC systems, use Sun Assembler
CONFIGURE_OPTIONS.sparc+= --without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386+= --with-gnu-as --with-as=/usr/bin/gas
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS.$(MACH))

CONFIGURE_OPTIONS+= BOOT_CFLAGS='-g -O2'
CONFIGURE_OPTIONS+= LDFLAGS="-R$(CONFIGURE_PREFIX)/lib"

COMPONENT_POST_INSTALL_ACTION = \
  $(RM) -r $(PROTO_DIR)$(CONFIGURE_PREFIX)/lib/gcc/$(GNU_TRIPLET)/$(COMPONENT_VERSION)/include-fixed

unexport SHELLOPTS

#
# Run the tests and generate a summary report, then output the summary
# report into the results file. Note that list of reported tests is sorted
# to allow parallel test run.
#
# To ensure that all tests that are expected to pass actually
# pass, we have to increase the stacksize limit to at least
# 16MB. Otherwise we'll get spurious failures in the test
# harness (gcc.c-torture/compile/limits-exprparen.c and others).
# With the soft stacksize limit set to 16384 we get reasonably good
# test results.
#
COMPONENT_PRE_TEST_ACTION += \
	(cd $(COMPONENT_TEST_DIR) ; \
	 ulimit -Ss 16385 ; \
	 $(ENV) $(COMPONENT_PRE_TEST_ENV) \
	        $(GMAKE) -k -i $(JOBS:%=-j%) check check-target RUNTESTFLAGS="--target_board=unix/\{,-msave-args\}" ; \
	 $(FIND) . -name  '*.sum' | while read f; do \
	        gsed -e '1,/^Running target unix/p' -e  'd' $f > $f.2; \
	        gsed -e '/^Running target unix/,/Summary ===$/p' -e  'd' $f | grep  '^.*: ' | sort -k 2 >> $f.2; \
	        gsed -e '/Summary ===$/,$p' -e  'd' $f >> $f.2; \
	        mv $f.2 $f; done; \
	 $(GMAKE) mail-report.log)

COMPONENT_TEST_CMD = $(CAT)
COMPONENT_TEST_TARGETS = mail-report.log

# Master test results are different between x86 and SPARC.
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)

# Required by test suite
REQUIRED_PACKAGES += developer/test/dejagnu
REQUIRED_PACKAGES += developer/build/autoconf-archive
REQUIRED_PACKAGES += developer/build/autogen
REQUIRED_PACKAGES += system/extended-system-utilities

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-8-runtime
REQUIRED_PACKAGES += system/library/gcc-8-runtime
REQUIRED_PACKAGES += system/library/gfortran-8-runtime
REQUIRED_PACKAGES += system/library/gobjc-8-runtime
REQUIRED_PACKAGES += system/library/math
