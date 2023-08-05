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
# Copyright (c) 2020, Andreas Wacknitz
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gmp
COMPONENT_VERSION=      6.3.0
COMPONENT_SUMMARY=      GNU Multiple Precision Bignum Library
COMPONENT_PROJECT_URL=  https://gmplib.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:ac28211a7cfb609bae2e2c8d6058d66c8fe96434f740cf6fe2e47b000d1c20cb
COMPONENT_FMRI=         library/gmp    
COMPONENT_CLASSIFICATION=Development/High Performance Computing
COMPONENT_LICENSE=      LGPLv3,GPLv3,FDLv1.3

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL = 0

PATH=$(dir $(CC)):/usr/bin:/usr/gnu/bin

CLOBBER_PATHS += libgmp.pc libgmpxx.pc

CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += -std=c99 
CFLAGS += -fexceptions
CPPFLAGS += $(CPP_POSIX) $(CPP_LARGEFILES)
LDFLAGS += $(LD_Z_REDLOCSYM) $(LD_Z_RESCAN_NOW)

# assembler detection for GNU MP and GNU MPFR is done via MPN_PATH
# at ./configure time. GNU MPFR wants to know GNU MP's MPN_PATH.
MPN32_i386 = x86/pentium x86 generic
MPN64_i386 = x86_64/pentium4 x86_64 generic
MPN32_sparc = sparc32/v9 sparc32 generic
MPN64_sparc = sparc64/ultrasparc34 sparc64/ultrasparc1234 sparc64 generic
MPN_32 = $(MPN32_$(MACH))
MPN_64 = $(MPN64_$(MACH))
GM4 = /usr/bin/gm4
GSED = /usr/bin/gsed
# libgmpxx.so.4 always gets built with unnecessary paths in RUNPATH/RPATH
ELFEDIT = /usr/bin/elfedit

CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CXX="$(CXX)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CC_BITS) $(CXXFLAGS)"
CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += CXXLD="$(CXX) $(CC_BITS) $(CXXFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += CPP_FOR_BUILD="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += CXXCPP="$(CXX) $(CC_BITS) $(CPPFLAGS) $(CXXFLAGS) -E"
CONFIGURE_ENV += INSTALL="$(INSTALL)"
CONFIGURE_ENV += CC_FOR_BUILD="$(CC) $(CPPFLAGS) $(CFLAGS)"
CONFIGURE_ENV += M4="$(GM4)"
CONFIGURE_ENV += SED="$(GSED)"
CONFIGURE_ENV += ABI="$(BITS)"
CONFIGURE_ENV += "MPN_PATH=$(MPN_$(BITS))"

CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock
CONFIGURE_OPTIONS += --disable-alloca
CONFIGURE_OPTIONS += --enable-cxx
CONFIGURE_OPTIONS += --enable-fft
CONFIGURE_OPTIONS += --disable-fat
CONFIGURE_OPTIONS += --with-pic

PROTOUSRSHAREINFODIR = $(PROTOUSRSHAREDIR)/info
PROTOUSRSHAREHTMLDIR = $(PROTOUSRSHAREDIR)/doc/gmp/html
PROTOUSRSHAREMAN3DIR = $(PROTOUSRSHAREDIR)/man/man3
PROTOUSRINCLUDEDIR = $(PROTOUSRDIR)/include
PROTOPKGCONFIGDIR = $(PROTOUSRLIBDIR)/pkgconfig
PROTOPKGCONFIGDIR64 = $(PROTOUSRLIBDIR64)/pkgconfig

GMP_SOVERSION=4.5.2

GCCLIBDIR  =$(GCC_ROOT)/lib
GCCLIBDIR64=$(GCC_ROOT)/lib/$(MACH64)

COMPONENT_POST_INSTALL_ACTION = \
    ( $(MKDIR) $(PROTOUSRSHAREHTMLDIR) ; \
      $(MKDIR) $(PROTOUSRSHAREMAN3DIR) ; \
      $(MKDIR) $(PROTOPKGCONFIGDIR) ; \
      $(MKDIR) $(PROTOPKGCONFIGDIR64) ; \
      $(ELFEDIT) -e "dyn:runpath $(GCCLIBDIR)" \
					$(PROTOUSRLIBDIR)/libgmpxx.so.$(GMP_SOVERSION) ; \
      $(ELFEDIT) -e "dyn:runpath $(GCCLIBDIR64)" \
					$(PROTOUSRLIBDIR64)/libgmpxx.so.$(GMP_SOVERSION) ; \
      $(ELFEDIT) -e "dyn:rpath $(GCCLIBDIR)" \
					$(PROTOUSRLIBDIR)/libgmpxx.so.$(GMP_SOVERSION) ; \
      $(ELFEDIT) -e "dyn:rpath $(GCCLIBDIR64)" \
					$(PROTOUSRLIBDIR64)/libgmpxx.so.$(GMP_SOVERSION) ; \
      $(GSED) -e "s/MACH64/$(MACH64)/g" \
					$(COMPONENT_DIR)/Solaris/libgmp-64.pc > $(COMPONENT_DIR)/libgmp.pc ; \
      $(GSED) -e "s/MACH64/$(MACH64)/g" \
					$(COMPONENT_DIR)/Solaris/libgmpxx-64.pc > \
							$(COMPONENT_DIR)/libgmpxx.pc ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/libgmp.pc \
					$(PROTOPKGCONFIGDIR) ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/libgmpxx.pc \
					$(PROTOPKGCONFIGDIR) ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/libgmp.pc \
					$(PROTOPKGCONFIGDIR64) ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/libgmpxx.pc \
					$(PROTOPKGCONFIGDIR64) ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/libgmp.3 \
					$(PROTOUSRSHAREMAN3DIR)/ )

ENV += -i

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
