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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ruby
COMPONENT_VERSION=	1.8.7
COMPONENT_PATCH_VERSION=	357
COMPONENT_PROJECT_URL=	http://www.ruby-lang.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-p$(COMPONENT_PATCH_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:5c64b63a597b4cb545887364e1fd1e0601a7aeb545e576e74a6d8e88a2765a37
COMPONENT_ARCHIVE_URL=	http://ftp.ruby-lang.org/pub/ruby/1.8/$(COMPONENT_ARCHIVE)
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_PATCH_VERSION)

# rubygems 
COMPONENT_SRC_1=	rubygems-1.3.5
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tgz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:c0928cc1ae54dedfb5f57ad3829882c1f90e42bc17bf50491aa6f93a937546ac
COMPONENT_ARCHIVE_URL_1=	http://production.cf.rubygems.org/rubygems/$(COMPONENT_ARCHIVE_1)

SOURCE_DIR_1=$(COMPONENT_DIR)/$(COMPONENT_SRC_1)
CLEAN_PATHS += $(SOURCE_DIR_1)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/configure.mk

# COMPONENT_VERSION <major>.<minor>.<teeny>
# is transformed into <major>.<minor> for RUBY_VER.
# First change the separator '.' to ' ', so we can use "word" to pull the 
# first two space-separated words from the string.
RUBY_VER_WORDS=	$(subst ., ,$(COMPONENT_VERSION))
RUBY_VER=$(word 1,$(RUBY_VER_WORDS)).$(word 2,$(RUBY_VER_WORDS))

GEMHOME=/var/ruby/$(RUBY_VER)/gem_home
PROTORUBYDIR=$(PROTO_DIR)/usr/ruby/$(RUBY_VER)
PROTOGEMHOME=$(PROTO_DIR)$(GEMHOME)
RUBYGEMS_INSTALL_TARGET=$(PROTORUBYDIR)/bin/gem

PROTO_RBCONFIG_FILE=$(PROTORUBYDIR)/lib/ruby/$(RUBY_VER)/$(MACH)-solaris$(SOLARIS_VERSION)/rbconfig.rb

# these macros are used in the package manifest
PKG_MACROS+=	RUBY_VER=$(RUBY_VER)

# Since configure.in is patched, we need to autoconf after the patch.
# Also, unpack the 2nd archive for rubygems.
# Rubygems does not have patches, nor does it use configure nor make.
COMPONENT_PREP_ACTION = (cd $(@D) ; autoconf); \
	$(RM) -r $(SOURCE_DIR_1); \
	$(UNPACK) $(UNPACK_ARGS) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)

# These modifications of ruby.1 must occur after ruby
# is installed, not before.  Although there are some other patches
# to ruby.1 that occur before, the ruby installation does some 
# formatting of ruby.1 that won't occur if the below changes
# are applied.
COMPONENT_POST_INSTALL_ACTION += \
	/bin/sed -f Solaris/ruby.1.sedscript \
	$(PROTORUBYDIR)/share/man/man1/ruby.1 > ruby.1.mod ; \
	$(MV) ruby.1.mod $(PROTORUBYDIR)/share/man/man1/ruby.1

# Fix generated rbconfig.rb.
# This should NOT occur until AFTER rubygems installs;
# otherwise the GEM_HOME setting added to rbconfig.rb will cause setup.rb
# to attempt (and fail) to install rubygems docs on the build system,
# rather than in the proto area.
# Also fix magic line of gem script.
POST_RUBYGEMS_INSTALL_ACTION += \
	/bin/sed -f Solaris/rbconfig.sedscript $(PROTO_RBCONFIG_FILE) \
	> rbconfig.rb.mod ; \
	$(MV) rbconfig.rb.mod $(PROTO_RBCONFIG_FILE) ; \
	/bin/sed -e '1s;^\#!/.*;\#!/usr/bin/ruby;' $(PROTORUBYDIR)/bin/gem \
	> gem.mod ; \
	$(MV) gem.mod $(PROTORUBYDIR)/bin/gem

# dtrace only available for i386 at this time;
# on sparc, a compiler bug (CR #6659110) prevents use of dtrace
DTRACE_FLAG_i386 =	--enable-dtrace
DTRACE_FLAG =		$(DTRACE_FLAG_$(MACH))

# dtrace.d, created in source dir during patch for dtrace,
# is needed for building
DTRACE_PRE_BUILD_i386 =	$(CP) $(SOURCE_DIR)/dtrace.d $(BUILD_DIR_32) 
DTRACE_PRE_BUILD =	$(DTRACE_PRE_BUILD_$(MACH))
COMPONENT_PRE_BUILD_ACTION =	$(DTRACE_PRE_BUILD)

# default LD_OPTION $(LD_B_DIRECT) causes problems--
# during install of ruby, ruby is executed and will core dump
# after compiling with this option
LD_B_DIRECT=

# don't use LD_Z_IGNORE: causes ruby linker problems with 
# unreferenced symbol tgetent in libreadline, similar to CR #6919344
LD_Z_IGNORE=

CONFIGURE_PREFIX =	$(USRDIR)/$(COMPONENT_NAME)/$(RUBY_VER)
CONFIGURE_OPTIONS += $(DTRACE_FLAG)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-install-doc
CONFIGURE_OPTIONS += --disable-option-checking
CONFIGURE_OPTIONS += --with-openssl
CONFIGURE_OPTIONS += --with-tk-dir=/usr
CONFIGURE_OPTIONS += --with-curses-dir=/usr
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"

include $(WS_TOP)/make-rules/shared-targets.mk

# common targets

build:		$(BUILD_32)

install:	build $(INSTALL_32) $(RUBYGEMS_INSTALL_TARGET)

# one expected failure in TestHTTP::HTTPConnectionTest
# also possibly test_endblockwarn(TestBeginEndBlock), 
# test_step_ruby_core_35753(TestRange)
test:	$(TEST_32)

# install rubygems using ruby installed in proto area
$(RUBYGEMS_INSTALL_TARGET):	$(INSTALL_32)
	(cd $(COMPONENT_SRC_1); $(ENV) - \
	"DESTDIR=$(PROTO_DIR)" \
	LD_LIBRARY_PATH=$(PROTORUBYDIR)/lib \
	GEM_HOME=$(PROTOGEMHOME) \
	$(PROTORUBYDIR)/bin/ruby \
	-I$(PROTORUBYDIR)/lib/ruby/1.8 \
	-I$(PROTORUBYDIR)/lib/ruby/1.8/$(MACH)-solaris$(SOLARIS_VERSION) \
	setup.rb --vendor --destdir=$(PROTO_DIR) )
	$(POST_RUBYGEMS_INSTALL_ACTION)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
