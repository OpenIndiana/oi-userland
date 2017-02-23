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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(USRBINDIR):$(GNUBIN)

COMPONENT_NAME=         mpfr
COMPONENT_VERSION=      2.4.2
COMPONENT_PROJECT_URL=	http://www.mpfr.org/
COMPONENT_ARCHIVE_HASH= \
    sha256:246d7e184048b1fc48d3696dd302c9774e24e921204221540745e5464022b637
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libmpfr
COMPONENT_ANITYA_ID=	2019

TPNO=			17709

include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS += libmpfr.pc
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

GMPINCDIR = $(USRINCDIR)/gmp
MPFRMULHIGH = 2048

COMPONENT_TEST_TRANSFORMS += \
     '-e "/libtool/d"' \
     '-e "/-m32/d"' \
     '-e "/-m64/d"' \
     '-e "/DEPDIR=/d"' \
     '-e "s/^make\[[0-9]\{1,\}\]/make/g"'

CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += INSTALL="$(INSTALL)"
CONFIGURE_ENV += SED="$(GSED)"
CONFIGURE_ENV += ABI="$(BITS)"
CONFIGURE_ENV += "MPN_PATH=$(MPN_$(BITS))"

CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/mpfr
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-libtool-lock
CONFIGURE_OPTIONS += --enable-thread-safe
CONFIGURE_OPTIONS += --enable-tests-timeout=0
CONFIGURE_OPTIONS += --with-gmp-include=$(GMPINCDIR)
CONFIGURE_OPTIONS += --with-gmp-lib=$(USRLIB.$(BITS))
CONFIGURE_OPTIONS += --with-mulhigh-size=$(MPFRMULHIGH)
CONFIGURE_OPTIONS += --with-pic

LINT_FLAGS += -I$(GMPINCDIR)

PROTOUSRSHAREHTMLDIR = $(PROTOUSRSHAREDOCDIR)/mpfr/html

COMPONENT_POST_INSTALL_ACTION = \
    ( $(MKDIR) $(PROTOUSRSHAREHTMLDIR) ; \
      $(MKDIR) $(PROTOUSRSHAREMAN3DIR) ; \
      $(MKDIR) $(PROTOPKGCONFIGDIR) ; \
      $(MKDIR) $(PROTOPKGCONFIGDIR64) ; \
      $(GSED) -e "s^\#include <gmp.h>^\#include <gmp/gmp.h>^g" \
	$(PROTOUSRINCDIR)/mpfr/mpfr.h > \
	$(PROTOUSRINCDIR)/mpfr/mpfr.h.sed ; \
      $(CP) -fp $(PROTOUSRINCDIR)/mpfr/mpfr.h.sed \
	$(PROTOUSRINCDIR)/mpfr/mpfr.h ; \
      $(RM) -f $(PROTOUSRINCDIR)/mpfr/mpfr.h.sed ; \
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

REQUIRED_PACKAGES += library/gmp
