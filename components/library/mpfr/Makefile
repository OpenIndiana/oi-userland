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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2016, Aurelien Larcher. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         mpfr
COMPONENT_VERSION=	4.2.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      The GNU Multiple Precision with IEEE Rounding Floating-Point Library
COMPONENT_PROJECT_URL=	https://www.mpfr.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:691db39178e36fc460c046591e4b0f2a52c8f2b3ee6d750cc2eab25f1eaa999d
COMPONENT_FMRI=			library/mpfr
COMPONENT_CLASSIFICATION=Development/High Performance Computing
COMPONENT_LICENSE=      LGPLv2.1,GPLv2,FDLv1.2	

include $(WS_MAKE_RULES)/common.mk

MPFR_PATCHLEVEL=9
IPS_COMPONENT_VERSION= $(COMPONENT_VERSION).$(MPFR_PATCHLEVEL)
HUMAN_VERSION= $(COMPONENT_VERSION)-p$(MPFR_PATCHLEVEL)

PATH = $(dir $(CC)):$(PATH.illumos)

CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += -std=c99 $(CPP_XPG6MODE)
LDFLAGS += $(LD_Z_REDLOCSYM) $(LD_Z_RESCAN_NOW)

MPN32_i386 = x86/pentium x86 generic
MPN64_i386 = x86_64/pentium4 x86_64 generic
MPN32_sparc = sparc32/v9 sparc32 generic
MPN64_sparc = sparc64/ultrasparc34 sparc64/ultrasparc1234 sparc64 generic
MPN32 = $(MPN32_$(MACH))
MPN64 = $(MPN64_$(MACH))

GMPLIBDIR_32 = /usr/lib
GMPLIBDIR_64 = /usr/lib/$(MACH64)
MPFRMULHIGH = 2048

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += INSTALL="$(INSTALL)"
CONFIGURE_ENV += SED="$(GSED)"
CONFIGURE_ENV += ABI="$(BITS)"
CONFIGURE_ENV += "MPN_PATH=$(MPN_$(BITS))"

CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock
CONFIGURE_OPTIONS += --enable-thread-safe
CONFIGURE_OPTIONS += --enable-tests-timeout=0
CONFIGURE_OPTIONS += --with-gmp-lib=$(GMPLIBDIR_$(BITS))
CONFIGURE_OPTIONS += --with-mulhigh-size=$(MPFRMULHIGH)
CONFIGURE_OPTIONS += --with-pic

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
