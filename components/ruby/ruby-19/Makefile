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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ruby
COMPONENT_VERSION=	1.9.3
COMPONENT_PATCH_VERSION=	551
COMPONENT_PROJECT_URL=	http://www.ruby-lang.org/
COMPONENT_SRC=	\
	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-p$(COMPONENT_PATCH_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bb5be55cd1f49c95bb05b6f587701376b53d310eb1bb7c76fbd445a1c75b51e8
COMPONENT_ARCHIVE_URL=	\
	http://ftp.ruby-lang.org/pub/ruby/1.9/$(COMPONENT_ARCHIVE)
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_PATCH_VERSION)
COMPONENT_BUGDB=	utility/ruby

TPNO=			15969

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/configure.mk

# COMPONENT_VERSION <major>.<minor>.<teeny>
# is transformed into <major>.<minor> for RUBY_VER.
# First change the separator '.' to ' ', so we can use "word" to pull the 
# first two space-separated words from the string.
RUBY_VER_WORDS=	$(subst ., ,$(COMPONENT_VERSION))
RUBY_VER=$(word 1,$(RUBY_VER_WORDS)).$(word 2,$(RUBY_VER_WORDS))
# the library-compatible version
RUBY_LIB_VER=1.9.1

PROTORUBYDIR=$(PROTO_DIR)/usr/ruby/$(RUBY_VER)
PROTO_RBCONFIG_FILE=$(PROTORUBYDIR)/lib/ruby/$(RUBY_LIB_VER)/i386-solaris$(SOLARIS_VERSION)/rbconfig.rb

# these macros are used in the package manifest
PKG_MACROS+=	RUBY_VER=$(RUBY_VER) RUBY_LIB_VER=$(RUBY_LIB_VER)

# Apply some of the edits here--including to the sed scripts themselves.
# These modifications of ruby.1 must occur after ruby
# is installed, not before.  Although there are some other patches
# to ruby.1 that occur before, the ruby installation does some 
# formatting of ruby.1 that won't occur if the below changes
# are applied.
# Fix generated rbconfig.rb using /usr/bin/sed; gsed doesn't 
# work for some of the commands in rbconfig.sedscript.
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -e "s/RUBY_VER/$(RUBY_VER)/" \
	    -e "s/RUBY_LIB_VER/$(RUBY_LIB_VER)/" Solaris/gem.1-generic \
	    > Solaris/gem.1 ; \
	$(GSED) -e "s/RUBY_VER/$(RUBY_VER)/" \
	    -e "s/RUBY_LIB_VER/$(RUBY_LIB_VER)/" Solaris/ruby.1.sedscript \
	    > Solaris/ruby.1.sedscript.mod ; \
	$(GSED) -e  "s/RUBY_VER/$(RUBY_VER)/" \
	    -e "s/RUBY_LIB_VER/$(RUBY_LIB_VER)/" Solaris/rbconfig.sedscript \
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

# i386 build runs into a Solaris ube compiler bug (#16775467) 
# while compiling load.c; it's having trouble with -xO4, so work around
# by using -xO3 instead.  16775467 was patched for 12.1 compiler, so
# the below should not no longer be necessary when we switch to 
# the 12.3 compiler
studio_OPT.i386.64 = -xO3

# sparc build sometimes fails with studio 12.3 because of 17537968.
studio_OPT.sparc.64 = -xO3

# without this define, config fails frequently on i386 when including 
# /usr/include/sys/isa_defs.h with error: "ISA not supported";
# many extensions don't get built and at least one error causes 
# the build to fail
studio_XBITS.i386.64 += -D__amd64

CONFIGURE_PREFIX =	$(USRDIR)/$(COMPONENT_NAME)/$(RUBY_VER)
# change CONFIGURE_BINDIR.64 because this path will be embedded in
# the header for ruby scripts; we are only building 64-bit,
# so the real path for ruby will not have $(MACH64) in it
CONFIGURE_BINDIR.64 =   $(CONFIGURE_BINDIR.32)
# not strictly needed, since ruby doesn't use sbin, but
# change this as well, for consistency with BINDIR
CONFIGURE_SBINDIR.64 =   $(CONFIGURE_SBINDIR.32)

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
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

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

include $(WS_TOP)/make-rules/shared-targets.mk

# common targets

build:		$(BUILD_32)

install:	build $(INSTALL_32)

test:	$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
