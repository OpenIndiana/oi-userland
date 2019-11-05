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

PREFERRED_BITS=	64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ruby
COMPONENT_VERSION=	2.6.3
COMPONENT_SUMMARY=	Ruby, RubyGems, and Rake
COMPONENT_PROJECT_URL=	http://www.ruby-lang.org/
COMPONENT_SRC=	\
	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:11a83f85c03d3f0fc9b8a9b6cad1b2674f26c5aaa43ba858d4b0fcc2b54171e1
COMPONENT_FMRI= runtime/ruby-26
COMPONENT_CLASSIFICATION= Development/Ruby
COMPONENT_LICENSE=      Ruby License
COMPONENT_LICENSE_FILE= COPYING


COMPONENT_ARCHIVE_URL=	\
	https://cache.ruby-lang.org/pub/ruby/2.6/$(COMPONENT_ARCHIVE)
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
RUBY_LIB_VER=2.6.0

PROTORUBYDIR=$(PROTO_DIR)/usr/ruby/$(RUBY_VER)
PROTO_RBCONFIG_FILE=$(PROTORUBYDIR)/lib/ruby/$(RUBY_LIB_VER)/$(MACH64)-solaris$(SOLARIS_VERSION)/rbconfig.rb

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
	    -e "s/RUBY_LIB_VER/$(RUBY_LIB_VER)/" \
	    -e "s,%%CC%%,$(CC)," \
	    -e "s,%%CXX%%,$(CXX)," \
	    Solaris/rbconfig.sedscript \
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

# Set the locale to generate documentation correctly
COMPONENT_BUILD_ENV += LC_ALL=en_US.UTF-8
COMPONENT_INSTALL_ENV += LC_ALL=en_US.UTF-8

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

COMPONENT_TEST_TRANSFORMS += \
    '-n' \
    '-e "s/Finished tests in .*s, .* tests\/s, .* assertions/Finished tests in Xs, X tests\/s, X assertions/"' \
    '-e "s/\(.*\) tests, .* assertions, \(.*\) failures, \(.*\) errors, .* skips/\1 tests, X assertions, \2 failures, \3 errors, X skips/"' \
    '-e "/^make/d"' \
    '-e "/fatal/Ip"' \
    '-e "/test succeeded/p"' \
    '-e "/Running tests/p"' \
    '-e "/Finished tests in Xs, X tests\/s, X assertions/p"' \
    '-e "/.* tests, X assertions, .* failures, .* errors, X skips/p"'

# common targets

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:	$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
