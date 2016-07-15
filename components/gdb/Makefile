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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
# There are a large number of macros in the GCB code written
# specifically for GCC's preprocessor. Studio does not expand
# these macros the same way GCC does, and the resulting gdb is
# not usable. Building gdb with a GCC >= 4.7.2 produces very
# good results, even on SPARC.
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gdb
COMPONENT_VERSION=	7.11
COMPONENT_ARCHIVE_HASH=	\
    sha256:9382f5534aa0754169e1e09b5f1a3b77d1fa8c59c1e57617e06af37cb29c669a

TPNO=			27358

# The traditional output from gmake test omits some
# test results information that is contained in the 
# build/<arch>/gdb/testsuite/gdb.sum file, so use that file instead
# for test results comparison.
COMPONENT_POST_TEST_ACTION += \
	( $(MV) $(COMPONENT_TEST_OUTPUT) $(COMPONENT_TEST_OUTPUT)-orig ; \
	$(CP) $(BUILD_DIR_64)/gdb/testsuite/gdb.sum $(COMPONENT_TEST_OUTPUT) )

# Results output is different on Intel vs. SPARC.
# Note that comparisons against master results 
# are not clean since results will still vary.
COMPONENT_TEST_MASTER = \
        $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH)-$(BITS).master

# Test transforms retain only relevant results output.
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/^FAIL/p" ' \
        '-e "/^KFAIL/p" ' \
        '-e "/^PASS/p" ' \
        '-e "/^UNRESOLVED/p" ' \
        '-e "/^UNSUPPORTED/p" ' \
        '-e "/^UNTESTED/p" ' \
        '-e "/^XFAIL/p" ' \
        '-e "/^\# of /p" '

# Test results vary from run to run and machine to machine,
# so master test results will not match, and are not
# appropriate for a full Userland test run
$(SKIP_TEST_AT_TOP_LEVEL)

include $(WS_MAKE_RULES)/gnu-component.mk


# GDB wants the GNU utilities
PATH=/usr/gnu/bin:$(GCC_ROOT)/bin:/usr/bin:/usr/perl/$(PERL_VERSION)/bin

# Specify the C Standard to use when building
CC += -std=gnu99

CFLAGS_sparc =	-g -O2 -mcpu=ultrasparc -mtune=ultrasparc
CFLAGS_sparc +=	-mno-unaligned-doubles
CFLAGS_sparc += -mapp-regs -mhard-float
CFLAGS_i386 =	-g -O2 -march=opteron -mtune=opteron
CFLAGS_EXTRA = -Wall -Wno-long-long -Wcast-align -fno-omit-frame-pointer

CFLAGS = $(CC_BITS) $(CFLAGS_EXTRA) $(CFLAGS_$(MACH))
CXXFLAGS = $(CC_BITS) $(CFLAGS_EXTRA) $(CFLAGS_$(MACH))
CPPFLAGS = -D_REENTRANT -I$(USRINCDIR)/ncurses

CONFIGURE_OPTIONS += --with-x=no
CONFIGURE_OPTIONS += --with-curses
CONFIGURE_OPTIONS += --disable-werror
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-tui
CONFIGURE_OPTIONS += --without-auto-load-safe-path
CONFIGURE_OPTIONS += --with-python=yes
CONFIGURE_OPTIONS += --with-libexpat-prefix=$(USRLIBDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --with-system-zlib


# Generate the newly added Solaris instruction and
# register tables which weren't there by default.
COMPONENT_PRE_CONFIGURE_ACTION = \
  ( cd  $(SOURCE_DIR)/gdb/features ; \
    $(GMAKE) all )

# Ensure PATH is set during build;
# need /usr/perl5/$(PERL_VERSION)/bin from PATH to access 
# pod2man perl script, used to create manpages
COMPONENT_BUILD_ENV += PATH=$(PATH)

# build the manpages
COMPONENT_POST_BUILD_ACTION = \
	( cd $(BUILD_DIR_64)/gdb/doc ; \
	$(GMAKE) man )

COMPONENT_POST_INSTALL_ACTION = \
  ( cd  $(PROTOUSRDIR)/share/gdb/python/gdb ; \
      $(PYTHON) -m compileall . ; \
    cd  $(PROTOUSRDIR)/share/gdb/python/gdb/command ; \
      $(PYTHON) -m compileall . ; \
    cd  $(PROTOUSRDIR)/share/gdb/python/gdb/function ; \
      $(PYTHON) -m compileall . ; \
    cd  $(PROTOUSRBINDIR)/ ; \
      /usr/bin/strip -x gdb ; \
    cd  $(COMPONENT_DIR) ; \
      $(INSTALL) -m 0755 $(COMPONENT_DIR)/Solaris/gdbtui \
	$(PROTOUSRBINDIR)/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-1  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-2  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-3  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-4  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-5  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-6  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-7  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/annotate.info  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/stabs.info  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(MKDIR) $(PROTOGNUSHAREMAN1) ; \
      $(MKDIR) $(PROTOUSRSHAREMAN1DIR) ; \
      $(INSTALL) -m 0444 $(BUILD_DIR_64)/gdb/doc/gdb.1 \
	$(PROTOUSRSHAREMAN1DIR) )

# Disable ASLR: it's a debugger and we do not want to risk
# altering the results of the debugging experiment.
ASLR_MODE=$(ASLR_DISABLE)

REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/texinfo
