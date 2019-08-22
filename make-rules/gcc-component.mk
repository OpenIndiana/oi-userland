#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Aurelien Larcher
#

GCC_COMPONENT_VERSION_MAJOR = $(shell echo $(COMPONENT_VERSION) | $(NAWK) -F. '{print $$1}')

ifeq ($(strip $(ILLUMOS_GCC_REVISION)),)
GCC_COMPONENT_STRING_VERSION = $(COMPONENT_VERSION)-oi-$(COMPONENT_REVISION)
else
GCC_COMPONENT_STRING_VERSION = $(COMPONENT_VERSION)-il-$(ILLUMOS_GCC_REVISION)
endif

GCC_COMPONENT_PREFIX = /usr/gcc/$(GCC_COMPONENT_VERSION_MAJOR)

#
# Define default component variables for upstream GCC
#
ifeq ($(strip $(COMPONENT_VERSION)),)
$(error Empty GCC version)
endif
ifeq ($(strip $(COMPONENT_ARCHIVE_HASH)),)
$(error Empty GCC archive hash)
endif
COMPONENT_NAME= gcc
COMPONENT_FMRI= developer/gcc-$(GCC_COMPONENT_VERSION_MAJOR)
COMPONENT_SUMMARY= GNU Compiler Collection
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_PROJECT_URL = http://gcc.gnu.org/
COMPONENT_SRC ?= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE ?= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL ?= \
  http://ftp.gnu.org/gnu/gcc/gcc-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

PATCH_EACH_ARCHIVE=1
PATCHDIR_PATCHES = $(shell find $(PATCH_DIR) -type f -name '$(PATCH_PATTERN)' \
                                2>/dev/null | sort) $(EXTRA_PATCHES)

MPFR_NAME= mpfr
ifeq ($(strip $(MPFR_VERSION)),)
$(error Empty MPFR version)
endif
ifeq ($(strip $(MPFR_ARCHIVE_HASH)),)
$(error Empty MPFR archive hash)
endif
COMPONENT_SRC_1=    $(MPFR_NAME)-$(MPFR_VERSION)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_URL_1= http://www.mpfr.org/$(COMPONENT_SRC_1)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= $(MPFR_ARCHIVE_HASH)
CLEAN_PATHS += $(COMPONENT_SRC_1)
COMPONENT_POST_UNPACK_ACTION_1 += ( $(RM) -r $(COMPONENT_SRC)/$(MPFR_NAME) && $(CP) -rpP $(COMPONENT_SRC_1) $(COMPONENT_SRC)/$(MPFR_NAME) )

MPC_NAME=mpc
ifeq ($(strip $(MPC_VERSION)),)
$(error Empty MPC version)
endif
ifeq ($(strip $(MPC_ARCHIVE_HASH)),)
$(error Empty MPC archive hash)
endif
COMPONENT_SRC_2= $(MPC_NAME)-$(MPC_VERSION)
COMPONENT_ARCHIVE_2= $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_URL_2=  http://www.multiprecision.org/mpc/download/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2= $(MPC_ARCHIVE_HASH)
CLEAN_PATHS += $(COMPONENT_SRC_2)
COMPONENT_POST_UNPACK_ACTION_2 += ( $(RM) -r $(COMPONENT_SRC)/$(MPC_NAME) && $(CP) -rpP $(COMPONENT_SRC_2) $(COMPONENT_SRC)/$(MPC_NAME) )

GMP_NAME=gmp
ifeq ($(strip $(GMP_VERSION)),)
$(error Empty GMP version)
endif
ifeq ($(strip $(GMP_ARCHIVE_HASH)),)
$(error Empty GMP archive hash)
endif
COMPONENT_SRC_3= $(GMP_NAME)-$(GMP_VERSION)
COMPONENT_ARCHIVE_3= $(COMPONENT_SRC_3).tar.bz2
COMPONENT_ARCHIVE_URL_3=  http://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE_3)
COMPONENT_ARCHIVE_HASH_3= $(GMP_ARCHIVE_HASH)
CLEAN_PATHS += $(COMPONENT_SRC_3)
COMPONENT_POST_UNPACK_ACTION_3 += ( $(RM) -r $(COMPONENT_SRC)/$(GMP_NAME) && $(CP) -rpP $(COMPONENT_SRC_3) $(COMPONENT_SRC)/$(GMP_NAME) )

BUILD_STYLE=configure

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CC_BITS=
CFLAGS= -O2
CXXFLAGS= -O2
FCFLAGS= -O2

COMMON_ENV=  LD_OPTIONS="-zignore -zcombreloc -i"
COMMON_ENV+= LD_FOR_TARGET=/usr/bin/ld
COMMON_ENV+= LD_FOR_HOST=/usr/bin/ld
COMMON_ENV+= LD=/usr/bin/ld

CONFIGURE_ENV+= $(COMMON_ENV)
COMPONENT_BUILD_ENV+= $(COMMON_ENV)
COMPONENT_INSTALL_ENV+= $(COMMON_ENV)

CONFIGURE_PREFIX=$(GCC_COMPONENT_PREFIX)

# General options
CONFIGURE_OPTIONS+= --sbindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --host $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --build $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --target $(GNU_TRIPLET)
#CONFIGURE_OPTIONS+= --with-boot-ldflags=-R$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS+= --with-pkgversion="OpenIndiana $(GCC_COMPONENT_STRING_VERSION)"
CONFIGURE_OPTIONS+= --with-bugurl="https://bugs.openindiana.org"

# Toolchain options
CONFIGURE_OPTIONS+= --without-gnu-ld
CONFIGURE_OPTIONS+= --with-ld=/usr/bin/ld
CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/$(GNU_TRIPLET)/bin

# On SPARC systems, use Sun Assembler
CONFIGURE_OPTIONS.sparc+= --without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386+= --with-gnu-as --with-as=/usr/bin/gas
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS.$(MACH))

# Set path to library install prefix
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
	        $(GMAKE) -k -i $(JOBS:%=-j%) check check-target RUNTESTFLAGS="--target_board=unix/-m64\{,-msave-args\}" ; \
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

# Common dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math

# Required by the test suite
REQUIRED_PACKAGES += developer/test/dejagnu
REQUIRED_PACKAGES += developer/build/autoconf-archive
REQUIRED_PACKAGES += developer/build/autogen
REQUIRED_PACKAGES += system/extended-system-utilities
