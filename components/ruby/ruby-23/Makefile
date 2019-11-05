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
COMPONENT_VERSION=	2.3.6
COMPONENT_PROJECT_URL=	http://www.ruby-lang.org/
COMPONENT_SRC=	\
	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e0d969ac22d4a403c1204868bb9c0d068aa35045bb3934cf50b17b7f66059f56

COMPONENT_ARCHIVE_URL=	\
	https://cache.ruby-lang.org/pub/ruby/2.3/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/ruby

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/configure.mk

# COMPONENT_VERSION <major>.<minor>.<teeny>
# is transformed into <major>.<minor> for RUBY_VER.
# First change the separator '.' to ' ', so we can use "word" to pull the
# first two space-separated words from the string.
RUBY_VER_WORDS=	$(subst ., ,$(COMPONENT_VERSION))
RUBY_VER=$(word 1,$(RUBY_VER_WORDS)).$(word 2,$(RUBY_VER_WORDS))
# the library-compatible version
RUBY_LIB_VER=2.3.0

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

CONFIGURE_PREFIX =	$(USRDIR)/$(COMPONENT_NAME)/$(RUBY_VER)

CONFIGURE_OPTIONS +=	--with-rubylibprefix=$(CONFIGURE_LIBDIR.32)/ruby
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--enable-rpath
CONFIGURE_OPTIONS +=	--enable-dtrace
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

CLEAN_PATHS +=		Solaris/gem.1 Solaris/rbconfig.sedscript.mod \
			Solaris/ruby.1.sedscript.mod

include $(WS_MAKE_RULES)/shared-targets.mk

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

# 16026 tests, 2239031 assertions, 0 failures, 1 errors, 47 skips
# RuntimeError: Error in TestGem#test_self_install_in_rescue
test:	$(TEST_32)

REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += runtime/ruby-23/ruby-tk
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
