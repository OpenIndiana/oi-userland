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
#

include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):/usr/bin:/usr/gnu/bin

COMPONENT_NAME=         gmp
COMPONENT_VERSION=      4.3.2
COMPONENT_PROJECT_URL=	http://gmplib.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:7be3ad1641b99b17f6a8be6a976f1f954e997c41e919ad7e0c418fe848c13c97
COMPONENT_ARCHIVE_URL=  http://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

PATCH_LEVEL = 0

CLOBBER_PATHS += libgmp.pc libgmpxx.pc

CFLAGS += -features=extinl,extensions
CFLAGS += -xustr=ascii_utf16_ushort -xcsi
# -xthreadvar=%all: allow thread-local storage via __thread
#  qualifier for all types of variables (global, static and dynamic)
CFLAGS += -xthreadvar=%all $(CPP_C99_EXTENDED_MATH)
CFLAGS += $(studio_C99_ENABLE) $(CPP_XPG6MODE)
CFLAGS += $(studio_PIC)
CXXFLAGS = -mt -features=anachronisms,except,rtti,export,extensions,nestedaccess,tmplife,tmplrefstatic
CXXFLAGS += -instances=global -template=geninlinefuncs -verbose=template
CXXFLAGS += -xbuiltin=%none -xinline=%auto -xlibmil
CXXFLAGS += -xustr=ascii_utf16_ushort -xlibmopt
CXXFLAGS += $(studio_cplusplus_C99_ENABLE) $(studio_PIC)
CXXFLAGS += $(CPP_XPG5MODE)
# -Qoption ccfe -features=zla: allow VLA/ZLA in C++ (like in C99)
CXXFLAGS += -Qoption ccfe -features=zla
CXXFLAGS += -xF=%none -xthreadvar=%all
CPPFLAGS += $(CPP_POSIX) $(CPP_LARGEFILES)
LDFLAGS += $(LD_Z_REDLOCSYM) $(LD_Z_RESCAN_NOW)

# assembler detection for GNU MP and GNU MPFR is done via MPN_PATH
# at ./configure time. GNU MPFR wants to know GNU MP's MPN_PATH.
MPN32_i386 = x86/pentium x86 generic
MPN64_i386 = x86_64/pentium4 x86_64 generic
MPN32_sparc = sparc32/v9 sparc32 generic
MPN64_sparc = sparc64 generic
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

CONFIGURE_OPTIONS += --includedir=/usr/include/gmp
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock
CONFIGURE_OPTIONS += --disable-alloca
CONFIGURE_OPTIONS += --enable-cxx
CONFIGURE_OPTIONS += --enable-fft
CONFIGURE_OPTIONS += --enable-mpbsd
CONFIGURE_OPTIONS += --disable-fat
CONFIGURE_OPTIONS += --with-pic

PROTOUSRSHAREINFODIR = $(PROTOUSRSHAREDIR)/info
PROTOUSRSHAREHTMLDIR = $(PROTOUSRSHAREDIR)/doc/gmp/html
PROTOUSRSHAREMAN3DIR = $(PROTOUSRSHAREDIR)/man/man3
PROTOUSRINCLUDEDIR = $(PROTOUSRDIR)/include
PROTOPKGCONFIGDIR = $(PROTOUSRLIBDIR)/pkgconfig
PROTOPKGCONFIGDIR64 = $(PROTOUSRLIBDIR64)/pkgconfig

COMPONENT_POST_INSTALL_ACTION = \
    ( $(MKDIR) $(PROTOUSRSHAREHTMLDIR) ; \
      $(MKDIR) $(PROTOUSRSHAREMAN3DIR) ; \
      $(MKDIR) $(PROTOPKGCONFIGDIR) ; \
      $(MKDIR) $(PROTOPKGCONFIGDIR64) ; \
      $(ELFEDIT) -e "dyn:runpath $(USRLIBDIR)" \
	$(PROTOUSRLIBDIR)/libgmpxx.so.4.1.2 ; \
      $(ELFEDIT) -e "dyn:runpath $(USRLIBDIR64)" \
	$(PROTOUSRLIBDIR64)/libgmpxx.so.4.1.2 ; \
      $(ELFEDIT) -e "dyn:rpath $(USRLIBDIR)" \
	$(PROTOUSRLIBDIR)/libgmpxx.so.4.1.2 ; \
      $(ELFEDIT) -e "dyn:rpath $(USRLIBDIR64)" \
	$(PROTOUSRLIBDIR64)/libgmpxx.so.4.1.2 ; \
      $(GSED) -e "s/MACH64/$(MACH64)/g" \
	$(COMPONENT_DIR)/Solaris/libgmp-64.pc > $(COMPONENT_DIR)/libgmp.pc ; \
      $(GSED) -e "s/MACH64/$(MACH64)/g" \
	$(COMPONENT_DIR)/Solaris/libgmpxx-64.pc > \
	    $(COMPONENT_DIR)/libgmpxx.pc ; \
      $(MV) $(PROTOUSRINCLUDEDIR)/gmp.h $(PROTOUSRINCLUDEDIR)/gmp/ ; \
      $(MV) $(PROTOUSRINCLUDEDIR)/mp.h $(PROTOUSRINCLUDEDIR)/gmp/ ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/index.html \
	$(PROTOUSRSHAREHTMLDIR)/ ; \
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

# common targets
build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

