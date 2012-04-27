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

COMPONENT_NAME=         mpfr
COMPONENT_VERSION=      2.4.2
COMPONENT_PROJECT_URL=	http://www.mpfr.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:246d7e184048b1fc48d3696dd302c9774e24e921204221540745e5464022b637
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

CLOBBER_PATHS += libmpfr.pc
PATCH_LEVEL = 0

CFLAGS += -features=extinl,extensions
CFLAGS += -xustr=ascii_utf16_ushort -xcsi
# -xthreadvar=%all: allow thread-local storage via __thread
#  qualifier for all types of variables (global, static and dynamic)
CFLAGS += -xthreadvar=%all -mt $(CPP_C99_EXTENDED_MATH)
CFLAGS += $(studio_C99_ENABLE) $(CPP_XPG6MODE)
CFLAGS += $(studio_PIC)
LDFLAGS += $(LD_Z_REDLOCSYM) $(LD_Z_RESCAN_NOW)

MPN32_i386 = x86/pentium x86 generic
MPN64_i386 = x86_64/pentium4 x86_64 generic
MPN32_sparc = sparc32/v9 sparc32 generic
MPN64_sparc = sparc64 generic
MPN32 = $(MPN32_$(MACH))
MPN64 = $(MPN64_$(MACH))

GMPINCDIR = /usr/include/gmp
GMPLIBDIR_32 = /usr/lib
GMPLIBDIR_64 = /usr/lib/$(MACH64)
MPFRMULHIGH = 2048

GSED = /usr/bin/gsed

CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += INSTALL="$(INSTALL)"
CONFIGURE_ENV += SED="$(GSED)"
CONFIGURE_ENV += ABI="$(BITS)"
CONFIGURE_ENV += "MPN_PATH=$(MPN_$(BITS))"

CONFIGURE_OPTIONS += --includedir=/usr/include/mpfr
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock
CONFIGURE_OPTIONS += --enable-thread-safe
CONFIGURE_OPTIONS += --enable-tests-timeout=0
CONFIGURE_OPTIONS += --with-gmp-include=$(GMPINCDIR)
CONFIGURE_OPTIONS += --with-gmp-lib=$(GMPLIBDIR_$(BITS))
CONFIGURE_OPTIONS += --with-mulhigh-size=$(MPFRMULHIGH)
CONFIGURE_OPTIONS += --with-pic

LINT_FLAGS += -I/usr/include/gmp

PROTOUSRSHAREINFODIR = $(PROTOUSRSHAREDIR)/info
PROTOUSRSHAREHTMLDIR = $(PROTOUSRSHAREDIR)/doc/mpfr/html
PROTOUSRSHAREMAN3DIR = $(PROTOUSRSHAREDIR)/man/man3
PROTOUSRINCLUDEDIR = $(PROTOUSRDIR)/include
PROTOPKGCONFIGDIR = $(PROTOUSRLIBDIR)/pkgconfig
PROTOPKGCONFIGDIR64 = $(PROTOUSRLIBDIR64)/pkgconfig

COMPONENT_POST_INSTALL_ACTION = \
    ( $(MKDIR) $(PROTOUSRSHAREHTMLDIR) ; \
      $(MKDIR) $(PROTOUSRSHAREMAN3DIR) ; \
      $(MKDIR) $(PROTOPKGCONFIGDIR) ; \
      $(MKDIR) $(PROTOPKGCONFIGDIR64) ; \
      $(GSED) -e "s^\#include <gmp.h>^\#include <gmp/gmp.h>^g" \
	$(PROTOUSRINCLUDEDIR)/mpfr/mpfr.h > \
	$(PROTOUSRINCLUDEDIR)/mpfr/mpfr.h.sed ; \
      $(CP) -fp $(PROTOUSRINCLUDEDIR)/mpfr/mpfr.h.sed \
	$(PROTOUSRINCLUDEDIR)/mpfr/mpfr.h ; \
      $(RM) -f $(PROTOUSRINCLUDEDIR)/mpfr/mpfr.h.sed ; \
      $(GSED) -e "s/MACH64/$(MACH64)/g" \
	$(COMPONENT_DIR)/Solaris/libmpfr-64.pc > $(COMPONENT_DIR)/libmpfr.pc ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/index.html \
	$(PROTOUSRSHAREHTMLDIR)/ ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/libmpfr.pc \
	$(PROTOPKGCONFIGDIR) ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/libmpfr.pc \
	$(PROTOPKGCONFIGDIR64) ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/libmpfr.3 \
	$(PROTOUSRSHAREMAN3DIR)/ )

# common targets
build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

