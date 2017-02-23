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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         isl
COMPONENT_VERSION=      0.12.2
COMPONENT_PROJECT_URL=  http://freecode.com/projects/isl
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:f4b3dbee9712850006e44f0db2103441ab3d13b406f77996d1df19ee89d11fb4
COMPONENT_ARCHIVE_URL=  http://isl.gforge.inria.fr/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        utility/gnu-compiler
COMPONENT_ANITYA_ID=	13286

TPNO=			23799

include $(WS_MAKE_RULES)/common.mk

# For the DEBUG_BUILD macro please see RFE/Bug 22185118:
# https://bug.oraclecorp.com/pls/bug/webbug_edit.edit_info_top?rptno=22185118
# For the GCC CFLAGS/CXXFLAGS please see:
# - RFE/Bug 22185134:
# https://bug.oraclecorp.com/pls/bug/webbug_edit.edit_info_top?rptno=22185134
# - RFE/Bug 22185167:
# https://bug.oraclecorp.com/pls/bug/webbug_edit.edit_info_top?rptno=22185167

COMPILER = gcc

PATCH_LEVEL = 0
DEBUG_BUILD := 0
PATH="$(GNUBIN):/usr/perl5/bin:$(USRBINDIR):$(USRSBINDIR)"

ISL_GCC_ARCH_i386 = -mtune=opteron -march=opteron
ISL_GCC_ARCH_i386 += -fno-strict-aliasing -fno-omit-frame-pointer
ISL_GCC_ARCH_sparc = -mtune=ultrasparc3 -mcpu=ultrasparc3 -mvis2 -mhard-float
ISL_GCC_ARCH_sparc += -fno-strict-aliasing -mno-unaligned-doubles -mimpure-text
ISL_GCC_ARCH = $(ISL_GCC_ARCH_$(MACH))
ISL_GCC_ARCH += -Wall -Wextra -Wcast-qual -Wcast-align

CFLAGS += $(CC_BITS)
ifeq ($(DEBUG_BUILD),1)
  CFLAGS += -g
endif
CFLAGS += -std=c99
CFLAGS += -D__C99FEATURES__
CFLAGS += -D_STDC_C99
CFLAGS += $(CPP_XPG6MODE)
CFLAGS += $(ISL_GCC_ARCH)

CXXFLAGS += $(CC_BITS)
ifeq ($(DEBUG_BUILD),1)
  CXXFLAGS += -g
endif
CXXFLAGS += -std=c++03
CXXFLAGS += $(CPP_XPG5MODE)
CXXFLAGS += $(ISL_GCC_ARCH)

CPPFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_POSIX)
CPPFLAGS += `pkg-config --cflags libgmp`
CPPFLAGS += `pkg-config --cflags libmpfr`

CONFIGURE_ENV +=	LD_OPTIONS="$(LD_OPTIONS)"
CONFIGURE_ENV +=	CCLD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV +=	LIBS="$(LIBS)"
CONFIGURE_ENV +=	PATH="$(PATH)"

CONFIGURE_OPTIONS  +=		--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--disable-option-checking
CONFIGURE_OPTIONS  +=		--disable-silent-rules
CONFIGURE_OPTIONS  +=		--enable-shared=yes
CONFIGURE_OPTIONS  +=		--enable-static=no
CONFIGURE_OPTIONS  +=		--disable-libtool-lock
CONFIGURE_OPTIONS  +=		--with-gcc-arch="$(ISL_GCC_ARCH)"
CONFIGURE_OPTIONS  +=		--with-pic
CONFIGURE_OPTIONS  +=		--with-int=gmp
CONFIGURE_OPTIONS  +=		--with-gmp=system
CONFIGURE_OPTIONS  +=		--with-gmp-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-clang=no

COMPONENT_TEST_ENV +=	libtool_install_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_ENV +=	libtool_execute_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"

COMPONENT_POST_INSTALL_ACTION = \
	( cd $(PROTOUSRDIR) ; \
	  $(PYTHON) -m compileall . ; \
	  $(MKDIR) $(PROTOUSRLIBDIR)/pkgconfig ; \
	  $(CP) $(COMPONENT_DIR)/Solaris/isl.pc \
	    $(PROTOUSRLIBDIR)/pkgconfig/ ; \
	  $(GSED) -i 's^LIBDIR^$(USRLIBDIR)^g' \
	    $(PROTOUSRLIBDIR)/pkgconfig/isl.pc ; \
	  $(MKDIR) $(PROTOUSRLIBDIR64)/pkgconfig ; \
	  $(CP) $(COMPONENT_DIR)/Solaris/isl.pc \
	    $(PROTOUSRLIBDIR64)/pkgconfig/ ; \
	  $(GSED) -i 's^LIBDIR^$(USRLIBDIR64)^g' \
	    $(PROTOUSRLIBDIR64)/pkgconfig/isl.pc )

COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-isl.master

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
     '-e "/test_input/d"' \
     '-e "/\.pip$$/d"' \
     '-e "/\.pwqp$$/d"' \
     '-e "/Making all/d"' \
     '-e "/Making check/d"' \
     '-e "/Nothing to be done/d"' \
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

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

REQUIRED_PACKAGES += library/gmp
