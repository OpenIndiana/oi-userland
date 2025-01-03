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
# Copyright 2023,2025 Friedrich Kink
# Copyright 2024, Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ruby
COMPONENT_VERSION=	3.4.1
COMPONENT_SUMMARY=	Ruby, RubyGems, and Rake
COMPONENT_PROJECT_URL=	https://www.ruby-lang.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://cache.ruby-lang.org/pub/ruby/3.4/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:018d59ffb52be3c0a6d847e22d3fd7a2c52d0ddfee249d3517a0c8c6dbfa70af
COMPONENT_FMRI=		runtime/ruby-34
COMPONENT_CLASSIFICATION= Development/Ruby
COMPONENT_LICENSE=	Ruby License
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += $(XPG7MODE)

# COMPONENT_VERSION <major>.<minor>.<teeny>
# is transformed into <major>.<minor> for RUBY_VER.
# First change the separator '.' to ' ', so we can use "word" to pull the
# first two space-separated words from the string.
RUBY_VER_WORDS=	$(subst ., ,$(COMPONENT_VERSION))
RUBY_VER= $(word 1,$(RUBY_VER_WORDS)).$(word 2,$(RUBY_VER_WORDS))
# the library-compatible version
RUBY_LIB_VER= $(RUBY_VER)

PROTORUBYDIR= $(PROTO_DIR)/usr/ruby/$(RUBY_VER)

ifeq ($(MACH), i386)
RUBY_CPU=x86_64
else
RUBY_CPU=sparc
endif

PROTO_RBCONFIG_FILE= $(PROTORUBYDIR)/lib/ruby/$(RUBY_LIB_VER)/$(RUBY_CPU)-solaris2.11/rbconfig.rb

# these macros are used in the package manifest
PKG_MACROS += RUBY_VER=$(RUBY_VER)
PKG_MACROS += RUBY_LIB_VER=$(RUBY_LIB_VER)
PKG_MACROS += RUBY_CPU=$(RUBY_CPU)

GENERATE_EXTRA_CMD += | $(GSED) -e 's|x86_64|$$(RUBY_CPU)|g'

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
	$(MV) rbconfig.rb.mod $(PROTO_RBCONFIG_FILE) ; \
	$(MW) $(PROTO_DIR)/usr/include $(PROTORUBYDIR) ;

COMPONENT_POST_INSTALL_ACTION += \
	encdir="$(PROTORUBYDIR)/lib/ruby/$(RUBY_LIB_VER)/$(RUBY_CPU)-solaris2.11/enc"; \
	filelist=`ls -1I trans $$encdir`; \
	subdirlist=`ls -1 $$encdir/trans`; \
        for f in $$filelist; \
	do \
          /usr/bin/elfedit -e 'dyn:runpath "$(USRDIR)/$(COMPONENT_NAME)/$(RUBY_VER)/lib/$(MACH64)"' $$encdir/$$f; \
	done; \
        for f in $$subdirlist; \
	do \
          /usr/bin/elfedit -e 'dyn:runpath "$(USRDIR)/$(COMPONENT_NAME)/$(RUBY_VER)/lib/$(MACH64)"' $$encdir/trans/$$f; \
	done;

# Set the locale to generate documentation correctly
COMPONENT_BUILD_ENV += LC_ALL=en_US.UTF-8
COMPONENT_INSTALL_ENV += LC_ALL=en_US.UTF-8
COMPONENT_INSTALL_ENV += HOME=/tmp

CONFIGURE_PREFIX =	$(USRDIR)/$(COMPONENT_NAME)/$(RUBY_VER)

CONFIGURE_OPTIONS +=	--with-rubylibprefix=$(CONFIGURE_LIBDIR.32)/ruby
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--enable-rpath
CONFIGURE_OPTIONS +=	--disable-dtrace
CONFIGURE_OPTIONS +=    --enable-yjit
CONFIGURE_OPTIONS +=    --enable-rjit
CONFIGURE_OPTIONS +=    --enable-debug-env
CONFIGURE_OPTIONS +=    --with-thread=pthread
CONFIGURE_OPTIONS +=    --with-rdoc=ri,html
CONFIGURE_OPTIONS +=    --with-ruby-version=$(RUBY_VER)
# Don't need docs for ruby C source files
CONFIGURE_OPTIONS +=	--disable-install-capi
CONFIGURE_OPTIONS +=	--disable-option-checking
CONFIGURE_OPTIONS +=	--with-openssl-dir=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

CLEAN_PATHS +=		Solaris/gem.1 Solaris/rbconfig.sedscript.mod \
			Solaris/ruby.1.sedscript.mod

COMPONENT_TEST_TRANSFORMS += \
    '-n' \
    '-e "s/Finished tests in .*s, .* tests\/s, .* assertions/Finished tests in Xs, X tests\/s, X assertions/"' \
    '-e "s/\(.*\) tests, .* assertions, \(.*\) failures, \(.*\) errors, .* skips/\1 tests, X assertions, \2 failures, \3 errors, X skips/"' \
    '-e "/^make/d"' \
    '-e "/^fatal:/d"' \
    '-e "/fatal/Ip"' \
    '-e "/test succeeded/p"' \
    '-e "/Running tests/p"' \
    '-e "/Finished tests in Xs, X tests\/s, X assertions/p"' \
    '-e "/.* tests, X assertions, .* failures, .* errors, X skips/p"'
COMPONENT_TEST_TRANSFORMS += ' | head -4'

# manually added dependencies
REQUIRED_PACKAGES += developer/lang/rustc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
