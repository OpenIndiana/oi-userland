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

USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gdb
COMPONENT_VERSION=      17.2
COMPONENT_REVISION=	0
COMPONENT_SUMMARY=      GDB: The GNU Project Debugger
COMPONENT_CLASSIFICATION=Development/System
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:cb891b9a9f554cac972eea5368176b240640ae90b681aae84bf873a9501f0063
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

# COMPONENT_TEST_ARGS+=RUNTESTFLAGS=gdb.base/a2-run.exp
COMPONENT_TEST_ARGS+= -j32

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
CONFIGURE_OPTIONS += --disable-slim
CONFIGURE_OPTIONS += --disable-werror
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-tui
CONFIGURE_OPTIONS += --without-auto-load-safe-path
CONFIGURE_OPTIONS += --with-python=$(PYTHON)
CONFIGURE_OPTIONS += --with-libexpat-prefix=/usr/lib
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --with-system-zlib
CONFIGURE_OPTIONS += --without-guile
# libbfd is provided by binutils
CONFIGURE_OPTIONS += --disable-install-libbfd

COMPONENT_BUILD_ENV += $(CONFIGURE_ENV)

# Generate illumos data files describing system calls and structures
# found in core files.
COMPONENT_POST_UNPACK_ACTION = \
    GCC_VERSION=$(GCC_VERSION) COMPONENT_DIR=$(COMPONENT_DIR) \
    SOURCE_DIR=$(SOURCE_DIR) \
    $(COMPONENT_DIR)/Solaris/gen_syscall_table.sh

# Generate the newly added Solaris instruction and
# register tables which weren't there by default.
XMLTOC+= i386/amd64-avx-illumos.xml
XMLTOC+= i386/amd64-illumos.xml
XMLTOC+= i386/i386-avx-illumos.xml
XMLTOC+= i386/i386-illumos.xml
XMLTOC+= i386/i386-mmx-illumos.xml

FEATURE_XMLFILES+= i386/32bit-illumos.xml
FEATURE_XMLFILES+= i386/64bit-illumos.xml

COMPONENT_PRE_CONFIGURE_ACTION += \
  ( cd  $(SOURCE_DIR)/gdb/features ; \
    $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) GDB=/usr/bin/gdb XMLTOC="$(XMLTOC)" FEATURE_XMLFILES="$(FEATURE_XMLFILES)" cfiles; )

# build the manpages
COMPONENT_POST_BUILD_ACTION = \
	+( cd $(BUILD_DIR_64)/gdb/doc ; \
    $(ENV) $(COMPONENT_BUILD_ENV) $(GMAKE) man; )

# tests hangs up the test run, so skip them.
SKIP_GDB_TEST+= gdb.mi/mi-exec-run.exp
SKIP_GDB_TEST+= gdb.base/annota3.exp
SKIP_GDB_TEST+= gdb.base/catch-fork-kill.exp
SKIP_GDB_TEST+= gdb.threads/local-watch-wrong-thread.exp
#   #error "not using SystemTap v3 probes" Running target unix
SKIP_GDB_TEST+= gdb.base/stap-probe.exp
SKIP_GDB_TEST+= gdb.trace/stap-trace.exp
# fatal error: asm/unistd.h: No such file or directory
SKIP_GDB_TEST+= gdb.threads/step-over-thread-exit-while-stop-all-threads.exp
SKIP_GDB_TEST+= gdb.threads/step-over-thread-exit.exp 
# fatal error: sys/ptrace.h: No such file or directory
SKIP_GDB_TEST+= gdb.base/attach-twice.exp
# ld: fatal: library -lm: not found
SKIP_GDB_TEST+= gdb.arch/aarch64-fp.exp 
SKIP_GDB_TEST+= gdb.base/break-entry.exp
SKIP_GDB_TEST+= gdb.base/watchpoints.exp
# attempt to include C-header as assembler code
# /usr/include/sys/int_types.h: Assembler messages:
SKIP_GDB_TEST+= gdb.arch/amd64-entry-value-inline.exp
SKIP_GDB_TEST+= gdb.arch/altivec-abi.exp
SKIP_GDB_TEST+= gdb.arch/riscv-info-fcsr.exp
SKIP_GDB_TEST+= gdb.arch/amd64-watchpoint-downgrade.exp
# ld: fatal: unrecognized option '--build-id'
SKIP_GDB_TEST+= gdb.base/watch_thread_num.exp
SKIP_GDB_TEST+= gdb.base/index-cache.exp
SKIP_GDB_TEST+= gdb.base/bigcore.exp
SKIP_GDB_TEST+= gdb.dwarf2/dw2-using-debug-str.exp
SKIP_GDB_TEST+= gdb.python/py-cmd.exp
SKIP_GDB_TEST+= gdb.python/py-missing-debug.exp
# ld: fatal: unrecognized option '--build-id=none'
SKIP_GDB_TEST+= gdb.base/jit-reader.exp
SKIP_GDB_TEST+= gdb.base/bp-cmds-sourced-script.exp
# ld: fatal: unrecognized option '--gc-sections'
SKIP_GDB_TEST+= gdb.base/siginfo.exp
# gcc: error: -pie is not supported in this configuration
SKIP_GDB_TEST+= gdb.base/dprintf-next.exp
SKIP_GDB_TEST+= gdb.base/ldbl_e308.exp
SKIP_GDB_TEST+= gdb.base/patch.exp
SKIP_GDB_TEST+= gdb.base/many-completions.exp
SKIP_GDB_TEST+= gdb.base/find.exp
SKIP_GDB_TEST+= gdb.disasm/mn10300.exp
# ld: fatal: unrecognized option '--ctf-variables'
SKIP_GDB_TEST+= gdb.base/gdbinit-history.exp
SKIP_GDB_TEST+= gdb.base/corefile2.exp
SKIP_GDB_TEST+= gdb.base/inferior-clone.exp
# ld: fatal: unrecognized option '-g'
SKIP_GDB_TEST+= gdb.base/infcall-nested-structs-c++.exp
# ld: fatal: option -z has illegal argument 'relro'
SKIP_GDB_TEST+= gdb.base/gcore-relro.exp
# ld: fatal: unrecognized option '--gdb-index'
SKIP_GDB_TEST+= gdb.base/gold-gdb-index.exp
# ld: fatal: unrecognized option '-T'
SKIP_GDB_TEST+= gdb.base/infoline-reloc-main-from-zero.exp
# ld: fatal: unrecognized option '--export-dynamic'
SKIP_GDB_TEST+= gdb.ctf/multi.exp
SKIP_GDB_TEST+= gdb.ctf/dwarf2-and-ctf.exp
# ld: warning: symbol 'glob' has differing types:
SKIP_GDB_TEST+= gdb.multi/bp-thread-specific.exp
SKIP_GDB_TEST+= gdb.multi/stop-all-on-exit.exp
SKIP_GDB_TEST+= gdb.multi/base.exp
# ld: fatal: unrecognized option '--strip-debug'
SKIP_GDB_TEST+= gdb.python/py-progspace-events.exp
# Undefined                   first referenced
SKIP_GDB_TEST+= gdb.python/py-connection-removed.exp
SKIP_GDB_TEST+= gdb.arch/i386-avx.exp
# In function 'funca':
SKIP_GDB_TEST+= gdb.python/py-framefilter.c
# ERROR: tcl error code TCL LOOKUP COMMAND, TCL READ VARNAME
SKIP_GDB_TEST+= libctf-lookup/lookup.exp
SKIP_GDB_TEST+= libctf-regression/libctf-repeat-cu.exp
SKIP_GDB_TEST+= libctf-regression/regression.exp
SKIP_GDB_TEST+= libctf-writable/writable.exp
SKIP_GDB_TEST+= gdb.base/complex-parts.exp
SKIP_GDB_TEST+= gdb.base/print-internal-string.exp
SKIP_GDB_TEST+= gdb.dap/attach.exp
SKIP_GDB_TEST+= gdb.dap/stop-at-main.exp
SKIP_GDB_TEST+= gdb.dap/log-message.exp
SKIP_GDB_TEST+= gdb.dap/cond-bp.exp
SKIP_GDB_TEST+= gdb.dap/cancel-launch.exp
SKIP_GDB_TEST+= gdb.dap/stack-format.exp
SKIP_GDB_TEST+= gdb.dap/ptrref.exp
SKIP_GDB_TEST+= gdb.dap/terminate.exp
SKIP_GDB_TEST+= gdb.dap/eof.exp
SKIP_GDB_TEST+= gdb.dap/children.exp
SKIP_GDB_TEST+= gdb.dap/bt-nodebug.exp
SKIP_GDB_TEST+= gdb.dap/line-zero.exp
SKIP_GDB_TEST+= gdb.dap/ada-arrays.exp
SKIP_GDB_TEST+= gdb.dap/args-env.exp
SKIP_GDB_TEST+= gdb.dap/hover.exp
SKIP_GDB_TEST+= gdb.dap/scopes.exp
SKIP_GDB_TEST+= gdb.dap/disassem.exp
SKIP_GDB_TEST+= gdb.dap/global.exp
SKIP_GDB_TEST+= gdb.dap/max-size.exp
SKIP_GDB_TEST+= gdb.dap/catch-exception.exp
SKIP_GDB_TEST+= gdb.debuginfod/crc_mismatch.exp
SKIP_GDB_TEST+= gdb.debuginfod/solib-with-soname.exp
SKIP_GDB_TEST+= gdb.debuginfod/build-id-no-debug-warning.exp
SKIP_GDB_TEST+= gdb.debuginfod/fetch_src_and_symbols.exp
SKIP_GDB_TEST+= gdb.dwarf2/gdb-index-tilde.exp
SKIP_GDB_TEST+= gdb.dwarf2/ada-linkage-name.exp
SKIP_GDB_TEST+= gdb.mi/mi-start.exp
SKIP_GDB_TEST+= gdb.mi/mi-memory-changed.exp
SKIP_GDB_TEST+= gdb.mi/mi-i-cmd.exp
SKIP_GDB_TEST+= gdb.mi/mi-thread-specific-bp.exp
SKIP_GDB_TEST+= gdb.mi/mi-thread-bp-deleted.exp
SKIP_GDB_TEST+= gdb.mi/mi-console.exp
SKIP_GDB_TEST+= gdb.mi/list-thread-groups-no-inferior.exp
SKIP_GDB_TEST+= gdb.mi/mi-var-rtti.exp
SKIP_GDB_TEST+= gdb.mi/mi-var-invalidate-shlib.exp
SKIP_GDB_TEST+= gdb.mi/mi-stack.exp
SKIP_GDB_TEST+= gdb.mi/mi-until.exp
SKIP_GDB_TEST+= gdb.mi/mi-vla-fortran.exp
SKIP_GDB_TEST+= gdb.mi/mi-break-qualified.exp
SKIP_GDB_TEST+= gdb.mi/mi-exit-code.exp
SKIP_GDB_TEST+= gdb.mi/mi-threads-interrupt.exp
SKIP_GDB_TEST+= gdb.mi/mi-catch-load.exp
SKIP_GDB_TEST+= gdb.mi/mi-var-display.exp
SKIP_GDB_TEST+= gdb.mi/mi-var-list-children-invalid-grandchild.exp
SKIP_GDB_TEST+= gdb.modula2/builtin-procedure-adr.exp
SKIP_GDB_TEST+= gdb.multi/multi-attach.exp
SKIP_GDB_TEST+= gdb.multi/tids.exp
SKIP_GDB_TEST+= gdb.multi/bp-thread-specific.exp
SKIP_GDB_TEST+= gdb.multi/multi-target-thread-find.exp
SKIP_GDB_TEST+= gdb.multi/multi-target-no-resumed.exp
SKIP_GDB_TEST+= gdb.python/py-events.exp
SKIP_GDB_TEST+= gdb.python/tui-window-factory.exp
SKIP_GDB_TEST+= gdb.reverse/getresuid-reverse.exp
SKIP_GDB_TEST+= gdb.reverse/time-reverse.exp
SKIP_GDB_TEST+= gdb.reverse/s390-mvcle.exp
SKIP_GDB_TEST+= gdb.reverse/step-reverse.exp
SKIP_GDB_TEST+= gdb.threads/multi-create.exp
SKIP_GDB_TEST+= gdb.threads/signal-delivered-right-thread.exp
SKIP_GDB_TEST+= gdb.threads/detach-step-over.exp
SKIP_GDB_TEST+= gdb.threads/non-ldr-exc-3.exp
SKIP_GDB_TEST+= gdb.threads/sigthread.exp
SKIP_GDB_TEST+= gdb.threads/bp_in_thread.exp
SKIP_GDB_TEST+= gdb.threads/pending-fork-event-detach.exp
SKIP_GDB_TEST+= gdb.threads/thread-bp-deleted.exp
SKIP_GDB_TEST+= gdb.xml/tdesc-reload.exp
# timeout
SKIP_GDB_TEST+= gdb.base/sigstep.exp
SKIP_GDB_TEST+= gdb.threads/multiple-step-overs.exp
SKIP_GDB_TEST+= gdb.threads/wp-replication.exp
SKIP_GDB_TEST+= gdb.threads/watchthreads.exp
SKIP_GDB_TEST+= gdb.threads/watchthreads2.exp
SKIP_GDB_TEST+= gdb.tui/flush-after-run.exp
# changing results
SKIP_GDB_TEST+= gdb.threads/attach-many-short-lived-threads.exp
SKIP_GDB_TEST+= gdb.threads/continue-pending-status.exp
SKIP_GDB_TEST+= gdb.threads/infcall-from-bp-cond-simple.exp
SKIP_GDB_TEST+= gdb.threads/manythreads.exp
SKIP_GDB_TEST+= gdb.threads/next-fork-exec-other-thread.exp
SKIP_GDB_TEST+= gdb.threads/threadcrash.exp
SKIP_GDB_TEST+= gdb.threads/schedlock.exp
SKIP_GDB_TEST+= gdb.threads/tls-core.exp
SKIP_GDB_TEST+= gdb.base/bp-cmds-continue-ctrl-c.exp
SKIP_GDB_TEST+= gdb.mi/new-ui-mi-sync.exp
SKIP_GDB_TEST+= gdb.threads/step-over-trips-on-watchpoint.exp
SKIP_GDB_TEST+=	gdb.btrace/event-tracing-gap.exp
SKIP_GDB_TEST+=	gdb.btrace/event-tracing.exp
SKIP_GDB_TEST+= gdb.threads/gcore-thread.exp

COMPONENT_PRE_TEST_ACTION += \
  ( cd $(SOURCE_DIR)/gdb/testsuite; \
    for F in $(SKIP_GDB_TEST); \
    do \
      if test -e $$F; \
      then \
        $(MV) $$F $$F-save; \
      fi; \
    done; \
    cd "$(BUILD_DIR_64)/gdb/testsuite/" ; \
    PATH=$(PATH) $(MAKE) site.exp ; \
    echo "set gdb_test_timeout 120" >> site.exp )

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
COMPONENT_TEST_ENV += PATH="$(GCC_BINDIR):$(PATH)" LD_LIBRARY_PATH="$(GCC_ROOT)/lib/$(MACH64)/"

GENERATE_EXTRA_CMD += | $(GNU_GREP) -v -E '/.*\.pyc$$'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += developer/babeltrace
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libxxhash
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES.python += runtime/python
