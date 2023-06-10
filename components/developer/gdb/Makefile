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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright 2017, 2021 Gary Mills
# Copyright 2019 Andreas Wacknitz
# Copyright 2023 Carsten Grzemba
#

# There are a large number of macros in the GDB code written
# specifically for GCC's preprocessor. Studio does not expand
# these macros the same way GCC does, and the resulting gdb is
# not usable. Building gdb with a GCC >= 4.7.2 produces very
# good results, even on SPARC.
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gdb
COMPONENT_VERSION=      13.2
COMPONENT_SUMMARY=      GDB: The GNU Project Debugger
COMPONENT_CLASSIFICATION=Development/System
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:7ead13d9e19fa0c57bb19104e1a5f67eefa9fc79f2e6360de491e8fddeda1e30
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/gdb/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/gdb/
COMPONENT_FMRI= developer/debug/gdb

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/common.mk

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

PATH = $(PATH.gnu)

CFLAGS_sparc =	-g -O2 -mcpu=ultrasparc -mtune=ultrasparc
CFLAGS_sparc +=	-mno-unaligned-doubles
CFLAGS_sparc += -mapp-regs -mhard-float
CFLAGS_i386 =	-g -O2 -march=opteron -mtune=opteron
CFLAGS_EXTRA = -Wall -Wno-long-long -Wcast-align -fno-omit-frame-pointer

CFLAGS = $(CC_BITS) $(CFLAGS_EXTRA) $(CFLAGS_$(MACH))
CXXFLAGS = $(CC_BITS) $(CFLAGS_EXTRA) $(CFLAGS_$(MACH))
CPPFLAGS = -D_REENTRANT -I$(USRINCDIR)/ncurses

LDFLAGS += -L/usr/gnu/lib/$(MACH64) -R/usr/gnu/lib/$(MACH64)

# `echo $(CFLAGS)` and `echo $(LDFLAGS)` used to
# work around problem with extra blank characters
# inserted into configrue option strings during
# nested configure invocations within the gdb build.

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"

CONFIGURE_DEFAULT_DIRS=no
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))

CONFIGURE_OPTIONS += --with-x=no
CONFIGURE_OPTIONS += --with-curses
CONFIGURE_OPTIONS += --disable-werror
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-tui
CONFIGURE_OPTIONS += --without-auto-load-safe-path
CONFIGURE_OPTIONS += --with-python=$(PYTHON)
CONFIGURE_OPTIONS += --with-libexpat-prefix=/usr/lib
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --with-system-zlib
CONFIGURE_OPTIONS += --without-guile

COMPONENT_BUILD_ENV += $(CONFIGURE_ENV)

# Generate illumos data files describing system calls and structures
# found in core files.
COMPONENT_POST_UNPACK_ACTION = \
    GCC_VERSION=$(GCC_VERSION) COMPONENT_DIR=$(COMPONENT_DIR) \
    SOURCE_DIR=$(SOURCE_DIR) \
    $(COMPONENT_DIR)/Solaris/gen_syscall_table.sh

# Generate the newly added Solaris instruction and
# register tables which weren't there by default.
COMPONENT_PRE_CONFIGURE_ACTION += \
  +( cd  $(SOURCE_DIR)/gdb/features ; \
    $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) all; )

# build the manpages
COMPONENT_POST_BUILD_ACTION = \
	+( cd $(BUILD_DIR_64)/gdb/doc ; \
    $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) man; )

# Two tests hangs up the test run, so skip them.
COMPONENT_PRE_TEST_ACTION += \
  ( cd $(SOURCE_DIR)/gdb/testsuite; \
    for F in gdb.mi/mi-exec-run.exp gdb.base/annota3.exp; \
    do \
      if test -e $$F; \
      then \
        $(MV) $$F $$F-save; \
      fi; \
    done )

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
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-8  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/annotate.info  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/stabs.info  \
	$(PROTOUSRSHAREDIR)/info/ ; \
	 )

# Disable ASLR: it's a debugger and we do not want to risk
# altering the results of the debugging experiment.
ASLR_MODE=$(ASLR_DISABLE)

# Testing needs to find C/C++ compiler
COMPONENT_TEST_ENV += PATH="$(GCC_BINDIR):$(PATH)"

GENERATE_EXTRA_CMD += | $(GNU_GREP) -v -E '/.*\.pyc$$'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += developer/babeltrace
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
