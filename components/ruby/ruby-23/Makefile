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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ruby
COMPONENT_VERSION=	2.3.1
COMPONENT_PROJECT_URL=	http://www.ruby-lang.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:b87c738cb2032bf4920fef8e3864dc5cf8eae9d89d8d523ce0236945c5797dcd
COMPONENT_ARCHIVE_URL=	\
	http://cache.ruby-lang.org/pub/ruby/2.3/$(COMPONENT_ARCHIVE)

TPNO=			31235

include $(WS_MAKE_RULES)/common.mk

# COMPONENT_VERSION <major>.<minor>.<teeny>
# is transformed into <major>.<minor> for RUBY_VER.
# First change the separator '.' to ' ', so we can use "word" to pull the 
# first two space-separated words from the string.
RUBY_VER_WORDS=	$(subst ., ,$(COMPONENT_VERSION))
RUBY_VER=$(word 1,$(RUBY_VER_WORDS)).$(word 2,$(RUBY_VER_WORDS))
# RUBY_VER_NO_DOT is just <major><minor>, like RUBY_VER but no
# '.' separating <major> and <minor>.  Used when editing manpages (see below).
RUBY_VER_NO_DOT=$(subst .,,$(RUBY_VER))
# the library-compatible version
RUBY_LIB_VER=2.3.0

PROTORUBYDIR=$(PROTOUSRDIR)/ruby/$(RUBY_VER)
PROTO_RBCONFIG_FILE=$(PROTORUBYDIR)/lib/ruby/$(RUBY_LIB_VER)/$(MACH64)-solaris$(SOLARIS_VERSION)/rbconfig.rb

# these macros are used in the package manifest
PKG_MACROS+=	RUBY_VER=$(RUBY_VER) RUBY_LIB_VER=$(RUBY_LIB_VER) RUBY_VER_NO_DOT=$(RUBY_VER_NO_DOT)

# Prevent re-compile of ripper.so during install, which would result in
# an erroneous full build directory in its RUNPATH.  The below change to 
# ext/ripper/Makefile is identical to what occurs during install
# and prevents its regeneration. 
COMPONENT_PRE_INSTALL_ACTION += \
	$(GSED) -i -e "s/^static: check/static: all/" $(BUILD_DIR_64)/ext/ripper/Makefile ; \
	$(TOUCH) -r $(BUILD_DIR_64)/ext/ripper/ripper.o $(BUILD_DIR_64)/ext/ripper/Makefile

# Apply some of the edits here--including to the sed scripts themselves.
# These modifications of ruby.1 must occur after ruby
# is installed, not before.  Although there are some other patches
# to ruby.1 that occur before, the ruby installation does some 
# formatting of ruby.1 that won't occur if the below changes
# are applied.
# Fix generated rbconfig.rb using /usr/bin/sed; gsed doesn't 
# work for some of the commands in rbconfig.sedscript.
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -e "s/RUBY_VER_NO_DOT/$(RUBY_VER_NO_DOT)/g" \
	    -e "s/RUBY_VER/$(RUBY_VER)/g" \
	    -e "s/RUBY_LIB_VER/$(RUBY_LIB_VER)/g" Solaris/gem.1-generic \
	    > Solaris/gem.1 ; \
	$(GSED) -e "s/RUBY_VER_NO_DOT/$(RUBY_VER_NO_DOT)/g" \
	    -e "s/RUBY_VER/$(RUBY_VER)/g" \
	    -e "s/RUBY_LIB_VER/$(RUBY_LIB_VER)/g" Solaris/ruby.1.sedscript \
	    > Solaris/ruby.1.sedscript.mod ; \
	$(GSED) -e  "s/RUBY_VER/$(RUBY_VER)/g" \
	    -e "s/RUBY_LIB_VER/$(RUBY_LIB_VER)/g" Solaris/rbconfig.sedscript \
	    > Solaris/rbconfig.sedscript.mod ; \
	$(GSED) -i -f Solaris/ruby.1.sedscript.mod \
	    $(PROTORUBYDIR)/share/man/man1/ruby.1 ; \
	/usr/bin/sed -f Solaris/rbconfig.sedscript.mod \
	$(PROTO_RBCONFIG_FILE) > rbconfig.rb.mod ; \
	$(MV) rbconfig.rb.mod $(PROTO_RBCONFIG_FILE)

# default LD_OPTION $(LD_B_DIRECT) causes problems--
# during install of ruby, ruby is executed and will core dump
# after compiling with this option
LD_B_DIRECT=

# don't use LD_Z_IGNORE: causes ruby linker problems with 
# unreferenced symbol tgetent in libreadline, similar to bug #15617172
LD_Z_IGNORE=

# sparc build sometimes fails with studio 12.3 because of 17537968;
# -xO3 worked around the problem. Also, iropt optimizer has a 
# an assertion failure when compiling ext/socket/raddrinfo.c,
# (CR 20704428); dropping down to -xO2 works around the bug.
studio_OPT.sparc.64 = -xO2

# without this define, config fails frequently on i386 when including 
# /usr/include/sys/isa_defs.h with error: "ISA not supported";
# many extensions don't get built and at least one error causes 
# the build to fail
studio_XBITS.i386.64 += -D__amd64

CONFIGURE_PREFIX =	$(USRDIR)/$(COMPONENT_NAME)/$(RUBY_VER)

# we are building 64-bit, but most of the ruby libraries (*.rb files)
# are non-bit-specfic text files, so don't put them under lib/$(MACH64).
# The 64-bit *.so libraries will be in the $(MACH64)-solaris$(SOLARIS_VERSION)
# arch directories under lib

CONFIGURE_OPTIONS +=	--with-rubylibprefix=$(CONFIGURE_LIBDIR.32)/ruby
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--enable-rpath
# Don't need docs for ruby C source files
CONFIGURE_OPTIONS +=	--disable-install-capi
CONFIGURE_OPTIONS +=	--disable-option-checking
CONFIGURE_OPTIONS +=	--with-openssl
# If Ruby is configured with __builtin_setjmp, may cause
# problems with gems compiled with gcc.  Studio compiler doesn't 
# report an error for __builtin_setjmp, but gcc would.
CONFIGURE_OPTIONS +=	--with-setjmp-type=_setjmp
CONFIGURE_OPTIONS +=	DTRACE="$(USRSBINDIR)/dtrace"
# ensure we use the 64-bit configuration file, not the 32-bit one
CONFIGURE_OPTIONS +=	--with-tclConfig-file=$(USRLIBDIR)/64/tclConfig.sh
	# set mantype to "man" so tool/mdoc2man.rb is used to convert
	# the manpages from doc to man format; otherwise mantype is "doc" and
	# headers we add to the manpages will not work properly
CONFIGURE_OPTIONS +=	--with-mantype=man

# fiddle.so (ext/fiddle) links to libffi, which does not define
# ffi_raw_size(), although its prototype is in libffi's 
# /usr/lib/libffi-3.0/include/ffi.h header file.  
# Defining FFI_NO_RAW_API avoids use of ffi_raw_size().
# This is a workaround to bug
# 17349280 - libffi is missing ffi_raw_size()
CFLAGS +=		-DFFI_NO_RAW_API

# keep ASLR disabled; 
# miniruby may core dump on sparc during build
ASLR_MODE =		$(ASLR_DISABLE)

CLEAN_PATHS +=		Solaris/gem.1 Solaris/rbconfig.sedscript.mod \
			Solaris/ruby.1.sedscript.mod

# Some tests produce warnings if HTTP_PROXY is set
COMPONENT_TEST_ENV += "--unset=HTTP_PROXY"

# This set of tests goes through thousands of entries in the passwd
# and group table, taking hours to run; move it aside so we skip it.
# There may also be spurious errors if group memberships are modified
# during testing.
COMPONENT_PRE_TEST_ACTION += \
	( if test -e $(SOURCE_DIR)/test/etc/test_etc.rb ; then \
	    $(MV) $(SOURCE_DIR)/test/etc/test_etc.rb \
	    $(SOURCE_DIR)/test/etc/test_etc.rb-save ; fi )

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^linking shared-object ripper.so$$/d" ' \
	'-e "s|^20[0-9][0-9]-[01][1-9]-[0-3][0-9].*|XXX_DATE_TIME_XXX|" ' \
	'-e "s|\(^[[:space:]]*CC = \).*|\1|" ' \
	'-e "s|\(^[[:space:]]*LD = \).*|\1|" ' \
	'-e "s|\(^[[:space:]]*LDSHARED = \).*|\1|" ' \
	'-e "s|\(^[[:space:]]*CFLAGS = \).*|\1|" ' \
	'-e "s|\(^[[:space:]]*XCFLAGS = \).*|\1|" ' \
	'-e "s|\(^[[:space:]]*CPPFLAGS = \).*|\1|" ' \
	'-e "s|\(^[[:space:]]*DLDFLAGS = \).*|\1|" ' \
	'-e "s|\(^[[:space:]]*SOLIBS = \).*|\1|" ' \
	'-e "s|\(^COLLECT_GCC=\).*|\1|" ' \
	'-e "s|\(^COLLECT_LTO_WRAPPER=\).*|\1|" ' \
	'-e "s|\(^Target: \).*|\1|" ' \
	'-e "s|\(^Configured with: \).*|\1|" ' \
	'-e "s|\(^gcc version \).*|\1|" ' \
	'-e "s|\(^pid \)[1-9][0-9]*|\1NUM|" ' \
	'-e "s|^\.[\.FES]\+|XXX_DOTS_XXX|" ' \
	'-e "s|\(Insecure world writable dir \).*\( in PATH, mode \)[0-7].*|\1XXX_DIR_XXX\2XXX_MODE_XXX|g" ' \
	'-e "s|\(^Driver is \).*|\1XXX_RUBY_VERSION_XXX|" ' \
	'-e "s|\(^Target is \).*|\1XXX_RUBY_VERSION_XXX|" ' \
	'-e "s|\(^Finished tests in \).*|\1|" ' \
        '-e "s|^[[:space:]]*[0-9]\+) \([FSE][a-z]\+:$$\)|NUM) \1|" ' \
	'-e "s|URI::HTTP:[0-9a-fx]\+ |URI::HTTP:0xXXX |" ' \
	'-e "s|\(.*\#test_no_memory_leak \).*:$$|\1XXX_RUBY_FILE_XXX:|" ' \
	'-e "s|/tmp/.*:[0-9]\+: |XXX_TMPFILE_XXX: |" ' \
	'-e "s|[0-9]\+\( tests, \)[0-9]\+\( assertions, \)[0-9]\+\( failures, \)[0-9]\+\( errors, \)[0-9]\+\( skips\)|XXX_NUM_XXX\1XXX_NUM_XXX\2XXX_NUM_XXX\3XXX_NUM_XXX\4XXX_NUM_XXX\5|" ' \
	'-e "s|\(^ruby -v: \).*|\1XXX_RUBY_VERSION_XXX|" ' \
	'-e "s|\(\[yes-test-all\] Error \)[0-9]\+$$|\1NUM|"'

# master test results are not entirely clean, so not
# appropriate to run at top level
$(SKIP_TEST_AT_TOP_LEVEL)

REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/linker
REQUIRED_PACKAGES += x11/library/libx11
