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

#
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cloog
COMPONENT_VERSION=	0.18.3
COMPONENT_PROJECT_URL=	http://www.cloog.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:460c6c740acb8cdfbfbb387156b627cf731b3837605f2ec0001d079d89c69734
COMPONENT_ARCHIVE_URL=	http://www.bastoul.net/cloog/pages/download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/cloog
COMPONENT_ANITYA_ID=	13279

TPNO=			23800

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL := 0
PKG_PROTO_DIRS += $(COMPONENT_DIR)/Solaris
PATH="$(GNUBIN):$(USRDIR)/perl5/bin:$(USRBINDIR):$(USRSBINDIR)"

# Don't use SSE3 or SSSE3 on Intel, because it's not completely portable.
# Do not tell GCC to assume strictly correct pointer aliasing. CLooG
# employs casts from incompatible pointer types.
# General-purpose SPARC incantations:
# - build for UltraSPARC-III (use fp registers for int whenever possible)
# - use VIS-2 Instructions whenever possible
# - there are no misaligned doubles in this code
# - don't do software float (we're not using quat-precision).
CLOOG_GCC_ARCH_i386 = -mtune=opteron -march=opteron -mno-sse3 -mno-ssse3
CLOOG_GCC_ARCH_i386 += -fno-omit-frame-pointer -fno-strict-aliasing
CLOOG_GCC_ARCH_sparc = -mtune=ultrasparc3 -mcpu=ultrasparc3 -mvis2 -mhard-float
CLOOG_GCC_ARCH_sparc += -fno-strict-aliasing -mno-unaligned-doubles
CLOOG_GCC_ARCH = $(CLOOG_GCC_ARCH_$(MACH))
CLOOG_GCC_ARCH += -Wall -Wextra -Wcast-qual -Wcast-align

CFLAGS = $(CC_BITS)
CFLAGS += -O2 -std=c99
CFLAGS += -D__C99FEATURES__
CFLAGS += -D_STDC_C99
CFLAGS += $(CPP_XPG6MODE)
CFLAGS += $(CLOOG_GCC_ARCH)
CFLAGS += -Wall -Wextra -Wcast-qual -Wcast-align

CXXFLAGS = $(CC_BITS)
CXXFLAGS += -O2 -std=c++03
CXXFLAGS += $(CPP_XPG5MODE)
CXXFLAGS += $(CLOOG_GCC_ARCH)
CXXFLAGS += -Wall -Wextra -Wcast-qual -Wcast-align

CPPFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += `pkg-config --cflags libgmp`
CPPFLAGS += `pkg-config --cflags libmpfr`
CPPFLAGS += `pkg-config --cflags isl`

CONFIGURE_ENV +=	LD_OPTIONS="$(LD_OPTIONS)"
CONFIGURE_ENV +=	CCLD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV +=	LIBS="$(LIBS)"
CONFIGURE_ENV +=	PATH="$(PATH)"

COMPONENT_BUILD_ENV += LD_OPTIONS="$(LD_OPTIONS)"

CONFIGURE_OPTIONS  +=		--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--disable-silent-rules
CONFIGURE_OPTIONS  +=		--disable-libtool-lock
CONFIGURE_OPTIONS  +=		--with-gcc-arch="$(CLOOG_GCC_ARCH)"
CONFIGURE_OPTIONS  +=		--with-isl=system
CONFIGURE_OPTIONS  +=		--with-isl-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-gmp=system
CONFIGURE_OPTIONS  +=		--with-gmp-prefix=$(CONFIGURE_PREFIX)

COMPONENT_POST_INSTALL_ACTION = \
  ( cd $(PROTOUSRDIR) ; \
    $(MKDIR) $(PROTOUSRLIBDIR)/pkgconfig ; \
    $(CP) $(COMPONENT_DIR)/Solaris/cloog-isl.pc \
      $(PROTOUSRLIBDIR)/pkgconfig/ ; \
    $(GSED) -i 's^LIBDIR^$(USRLIBDIR)^g' \
      $(PROTOUSRLIBDIR)/pkgconfig/cloog-isl.pc ; \
    $(MKDIR) $(PROTOUSRLIBDIR64)/pkgconfig ; \
    $(CP) $(COMPONENT_DIR)/Solaris/cloog-isl.pc \
      $(PROTOUSRLIBDIR64)/pkgconfig/ ; \
    $(GSED) -i 's^LIBDIR^$(USRLIBDIR64)^g' \
      $(PROTOUSRLIBDIR64)/pkgconfig/cloog-isl.pc )

COMPONENT_TEST_ENV +=   libtool_install_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_ENV +=   libtool_execute_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_ENV +=	$(TEST_PATH)
COMPONENT_TEST_ENV +=	$(TARGET_ENV)

COMPONENT_TEST_MASTER = \
        $(COMPONENT_TEST_RESULTS_DIR)/results-cloog.master

COMPONENT_TEST_TRANSFORMS += \
     '-e "/libtool/d"' \
     '-e "/-m32/d"' \
     '-e "/-m64/d"' \
     '-e "/ld: warning/d"' \
     '-e "/warning/d"' \
     '-e "/prototype:/d"' \
     '-e "/argument/d"' \
     '-e "/Entering/d"' \
     '-e "/Leaving/d"' \
     '-e "/check-TESTS/d"' \
     '-e "/all-recursive/d"' \
     '-e "/Making all/d"' \
     '-e "/Making check/d"' \
     '-e "/gnu/d"' \
     '-e "/Nothing to be done/d"' \
     '-e "/is up to date/d"' \
     '-e "s/[0-9]\{1,\}\.[0-9]\{1,\} s, //g"' \
     '-e "s^[0-9]\{1,\} kB/s^^g"'  \
     '-e "s^[0-9]\{1,\}  kB/s^^g"'  \
     '-e "s^[0-9]\{1,\}\.[0-9]\{1,\}  MB/s^^g"' \
     '-e "s^[0-9]\{1,\}\.[0-9]\{1,\} MB/s^^g"' \
     '-e "s/([0-9]\{1,\} B)//g"' \
     '-e "s/([0-9]\{1,\}  B)//g"' \
     '-e "s/copied,/copied/g"'  \
     '-e "s/ \{1,\}copied/ copied/g"'  \
     '-e "s/copied $$/copied/g"'  \
     '-e "s/copied [0-9]\{1,\}\./copied/g"'

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += library/isl
