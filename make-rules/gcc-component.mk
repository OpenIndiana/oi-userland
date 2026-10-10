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
COMPONENT_FMRI= developer/gcc-$(GCCVER)
COMPONENT_SUMMARY= GNU Compiler Collection
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_PROJECT_URL = https://gcc.gnu.org/
COMPONENT_SRC ?= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE ?= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL ?= \
  https://ftp.gnu.org/gnu/gcc/gcc-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

PATCH_EACH_ARCHIVE=1
PATCHDIR_PATCHES = $(shell $(FIND) $(PATCH_DIR) -type f -name '$(PATCH_PATTERN)' \
                                2>/dev/null | $(SORT))

MPFR_NAME= mpfr
ifeq ($(strip $(MPFR_VERSION)),)
$(error Empty MPFR version)
endif
MPFR_ARCHIVE_HASH.4.0.2 =	sha256:c05e3f02d09e0e9019384cdd58e0f19c64e6db1fd6f5ecf77b4b1c61ca253acc
MPFR_ARCHIVE_HASH.4.2.0 =	sha256:691db39178e36fc460c046591e4b0f2a52c8f2b3ee6d750cc2eab25f1eaa999d
MPFR_ARCHIVE_HASH.4.2.1 =	sha256:b9df93635b20e4089c29623b19420c4ac848a1b29df1cfd59f26cab0d2666aa0
MPFR_ARCHIVE_HASH.4.2.2 =	sha256:9ad62c7dc910303cd384ff8f1f4767a655124980bb6d8650fe62c815a231bb7b
MPFR_ARCHIVE_HASH ?=		$(MPFR_ARCHIVE_HASH.$(MPFR_VERSION))
ifeq ($(strip $(MPFR_ARCHIVE_HASH)),)
$(error Empty MPFR archive hash)
endif
COMPONENT_SRC_1=    $(MPFR_NAME)-$(MPFR_VERSION)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_URL_1= https://www.mpfr.org/$(COMPONENT_SRC_1)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= $(MPFR_ARCHIVE_HASH)
CLEAN_PATHS += $(COMPONENT_SRC_1)
COMPONENT_POST_UNPACK_ACTION_1 += ( $(RM) -r $(COMPONENT_SRC)/$(MPFR_NAME) && $(CP) -rpP $(COMPONENT_SRC_1) $(COMPONENT_SRC)/$(MPFR_NAME) )

MPC_NAME=mpc
ifeq ($(strip $(MPC_VERSION)),)
$(error Empty MPC version)
endif
MPC_ARCHIVE_HASH.1.1.0 =	sha256:6985c538143c1208dcb1ac42cedad6ff52e267b47e5f970183a3e75125b43c2e
MPC_ARCHIVE_HASH.1.3.1 =	sha256:ab642492f5cf882b74aa0cb730cd410a81edcdbec895183ce930e706c1c759b8
MPC_ARCHIVE_HASH.1.4.1 =	sha256:91204cd32f164bd3b7c992d4a6a8ce6519511aadab30f78b6982d0bf8d73e931
MPC_ARCHIVE_HASH ?=		$(MPC_ARCHIVE_HASH.$(MPC_VERSION))
ifeq ($(strip $(MPC_ARCHIVE_HASH)),)
$(error Empty MPC archive hash)
endif
COMPONENT_SRC_2= $(MPC_NAME)-$(MPC_VERSION)
ifeq ($(strip $(MPC_VERSION)),1.4.1)
COMPONENT_ARCHIVE_2= $(COMPONENT_SRC_2).tar.xz
else
COMPONENT_ARCHIVE_2= $(COMPONENT_SRC_2).tar.gz
endif
COMPONENT_ARCHIVE_URL_2=  https://ftp.gnu.org/gnu/mpc/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2= $(MPC_ARCHIVE_HASH)
CLEAN_PATHS += $(COMPONENT_SRC_2)
COMPONENT_POST_UNPACK_ACTION_2 += ( $(RM) -r $(COMPONENT_SRC)/$(MPC_NAME) && $(CP) -rpP $(COMPONENT_SRC_2) $(COMPONENT_SRC)/$(MPC_NAME) )

GMP_NAME=gmp
ifeq ($(strip $(GMP_VERSION)),)
$(error Empty GMP version)
endif
GMP_ARCHIVE_HASH.6.1.2 =	sha256:5275bb04f4863a13516b2f39392ac5e272f5e1bb8057b18aec1c9b79d73d8fb2
GMP_ARCHIVE_HASH.6.2.1 =	sha256:eae9326beb4158c386e39a356818031bd28f3124cf915f8c5b1dc4c7a36b4d7c
GMP_ARCHIVE_HASH.6.3.0 =	sha256:ac28211a7cfb609bae2e2c8d6058d66c8fe96434f740cf6fe2e47b000d1c20cb
GMP_ARCHIVE_HASH ?=		$(GMP_ARCHIVE_HASH.$(GMP_VERSION))
ifeq ($(strip $(GMP_ARCHIVE_HASH)),)
$(error Empty GMP archive hash)
endif
COMPONENT_SRC_3= $(GMP_NAME)-$(GMP_VERSION)
COMPONENT_ARCHIVE_3= $(COMPONENT_SRC_3).tar.bz2
COMPONENT_ARCHIVE_URL_3=  https://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE_3)
COMPONENT_ARCHIVE_HASH_3= $(GMP_ARCHIVE_HASH)
CLEAN_PATHS += $(COMPONENT_SRC_3)
COMPONENT_POST_UNPACK_ACTION_3 += ( $(RM) -r $(COMPONENT_SRC)/$(GMP_NAME) && $(CP) -rpP $(COMPONENT_SRC_3) $(COMPONENT_SRC)/$(GMP_NAME) )

BUILD_STYLE=configure

include $(WS_MAKE_RULES)/common.mk

#
# Warning!
#
# The order of the following three blocks (setting of CONFIGURE_PREFIX,
# GCC_ROOT, and GCCVER) is important and should never be changed.
#

# The GCC_ROOT (set in shared-macros.mk) contains the path where we want to
# install the currently built gcc component.  We need to set CONFIGURE_PREFIX
# to the value of GCC_ROOT, but we do not want its full expansion because
# GCCVER does not contain the correct value yet.  It will be set below.  We
# must do this before we force the GCC_ROOT expansion below.
$(eval CONFIGURE_PREFIX = $(value GCC_ROOT))

# Make sure GCC_ROOT points to the GCC used to build the gcc component so we
# are able to find GCC in a case we build new major GCC version.  We need this
# because GCC_ROOT in shared-macros.mk is defined using the GCCVER and we need
# to change GCCVER (see below) to version of the currently built gcc component.
GCC_ROOT := $(GCC_ROOT)

# Override GCCVER so it points to the currently built gcc component version.
# This is needed to make sure all affected macros expand to the currently built
# GCC version and not to the version used to build this component.  The only
# exception to this rule is GCC_ROOT (see above).
GCCVER = $(firstword $(subst ., ,$(HUMAN_VERSION)))

PATH=$(PATH.gnu)

CC_BITS=
CFLAGS= -O2
CXXFLAGS= -O2
FCFLAGS= -O2

COMMON_ENV=  LD_OPTIONS="-zignore -zcombreloc -i"
COMMON_ENV+= LD_FOR_TARGET=$(LD)
COMMON_ENV+= LD_FOR_HOST=$(LD)
COMMON_ENV+= STRIP="/usr/bin/strip -x"
COMMON_ENV+= STRIP_FOR_TARGET="/usr/bin/strip -x"
COMMON_ENV+= LD=$(LD)

CONFIGURE_ENV+= $(COMMON_ENV)
COMPONENT_BUILD_ENV+= $(COMMON_ENV)
COMPONENT_INSTALL_ENV+= $(COMMON_ENV)

# We need info files in versioned subdir
CONFIGURE_INFODIR = $(CONFIGURE_PREFIX)/share/info

# General options
CONFIGURE_OPTIONS+= --sbindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --host $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --build $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --target $(GNU_TRIPLET)
CONFIGURE_OPTIONS+= --with-pkgversion="OpenIndiana $(GCC_COMPONENT_STRING_VERSION)"
CONFIGURE_OPTIONS+= --with-bugurl="https://bugs.openindiana.org"

# Toolchain options
CONFIGURE_OPTIONS+= --without-gnu-ld
CONFIGURE_OPTIONS+= --with-ld=$(LD)
CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/$(GNU_TRIPLET)/bin

# If the compiler used to build matches the compiler being built, there is no
# need for a 3 stage build.
CONFIGURE_OPTIONS += $(if $(strip $(shell $(CC) --version | $(GNU_GREP) $(COMPONENT_VERSION))),--disable-bootstrap,)
COMPONENT_BUILD_TARGETS = $(if $(strip $(shell $(CC) --version | $(GNU_GREP) $(COMPONENT_VERSION))),,bootstrap)

# The Sun Assembler is only used on SPARC gates.
CONFIGURE_OPTIONS+= --with-gnu-as --with-as=/usr/bin/gas

# Set path to library install prefix
CONFIGURE_OPTIONS+= LDFLAGS="-R$(CONFIGURE_PREFIX)/lib"

# Strip the resulting binaries
COMPONENT_INSTALL_TARGETS = install-strip

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
ifeq   ($(strip $(MACH)),i386)
COMPONENT_PRE_TEST_ACTION += \
	(cd $(COMPONENT_TEST_DIR) ; \
	 ulimit -Ss 16385 ; \
	 $(ENV) $(COMPONENT_PRE_TEST_ENV) \
	        $(GMAKE) -k -i $(PARALLEL_JOBS:%=-j%) check RUNTESTFLAGS="--target_board=unix/-m64\{,-msave-args\}" ; \
	 $(FIND) . -name  '*.sum' | while read f; do \
	        $(GSED) -e '1,/^Running target unix/p' -e  'd' $f > $f.2; \
	        $(GSED) -e '/^Running target unix/,/Summary ===$/p' -e  'd' $f | $(GNU_GREP) '^.*: ' | $(SORT) -k 2 >> $f.2; \
	        $(GSED) -e '/Summary ===$/,$p' -e  'd' $f >> $f.2; \
	        mv $f.2 $f; done; \
	 $(GMAKE) mail-report.log)
else
COMPONENT_PRE_TEST_ACTION += \
	(cd $(COMPONENT_TEST_DIR) ; \
	 ulimit -Ss 16385 ; \
	 $(ENV) $(COMPONENT_PRE_TEST_ENV) \
	        $(GMAKE) -k -i $(PARALLEL_JOBS:%=-j%) check RUNTESTFLAGS="--target_board=unix/-m64" ; \
	 $(FIND) . -name  '*.sum' | while read f; do \
	        $(GSED) -e '1,/^Running target unix/p' -e  'd' $f > $f.2; \
	        $(GSED) -e '/^Running target unix/,/Summary ===$/p' -e  'd' $f | $(GNU_GREP) '^.*: ' | $(SORT) -k 2 >> $f.2; \
	        $(GSED) -e '/Summary ===$/,$p' -e  'd' $f >> $f.2; \
	        mv $f.2 $f; done; \
	 $(GMAKE) mail-report.log)
endif

COMPONENT_TEST_CMD = $(CAT)
COMPONENT_TEST_TARGETS = mail-report.log

# Master test results are different between x86 and SPARC.
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

# Build and test dependencies
USERLAND_REQUIRED_PACKAGES += developer/build/autoconf-archive
USERLAND_REQUIRED_PACKAGES += developer/build/autogen
USERLAND_REQUIRED_PACKAGES += system/extended-system-utilities
USERLAND_TEST_REQUIRED_PACKAGES += developer/test/dejagnu
