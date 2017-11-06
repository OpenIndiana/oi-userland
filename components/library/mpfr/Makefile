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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         mpfr
COMPONENT_VERSION=      3.1.6
IPS_COMPONENT_VERSION=  3.1.6.1
COMPONENT_SUMMARY=      The GNU Multiple Precision with IEEE Rounding Floating-Point Library
COMPONENT_PROJECT_URL=	http://www.mpfr.org/
COMPONENT_FMRI=					library/mpfr
COMPONENT_CLASSIFICATION=Development/High Performance Computing
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
    sha256:cf4f4b2d80abb79e820e78c8077b6725bbbb4e8f41896783c899087be0e94068
COMPONENT_LICENSE=      LGPLv2.1,GPLv2,FDLv1.2	

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(dir $(CC)):$(PATH.illumos)

CLOBBER_PATHS += libmpfr.pc

CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += -std=c99 $(CPP_XPG6MODE)
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

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
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
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/libmpfr.pc \
				$(PROTOPKGCONFIGDIR) ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/libmpfr.pc \
				$(PROTOPKGCONFIGDIR64) ; \
      $(INSTALL) -m 0644 $(COMPONENT_DIR)/Solaris/libmpfr.3 \
				$(PROTOUSRSHAREMAN3DIR)/ )

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
