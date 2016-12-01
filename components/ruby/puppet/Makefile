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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		puppet
COMPONENT_VERSION=	3.8.6
COMPONENT_SUMMARY=	Puppet - configuration management toolkit
COMPONENT_PROJECT_URL=	http://puppetlabs.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:99ccccd1016d30914f69d96355002818aa8087dfb9e1e6e40578aa67fee77da8
COMPONENT_ARCHIVE_URL=	https://downloads.puppetlabs.com/puppet/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/management/puppet
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	puppet.license
COMPONENT_CLASSIFICATION=	System/Administration and Configuration

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/install.rb.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/ruby.mk

# puppet requires facter and hiera as part of the install phase
FACTER_LIB=$(WS_TOP)/components/ruby/facter/build/$(MACH32)/lib
HIERA_LIB=$(WS_TOP)/components/ruby/hiera/build/$(MACH32)/lib
COMPONENT_INSTALL_ENV   += RUBYLIB="$(FACTER_LIB):$(HIERA_LIB)"

../facter/build/%/.installed:
	(cd ../facter ; $(GMAKE) install)

../hiera/build/%/.installed:
	(cd ../hiera ; $(GMAKE) install)

# set the bindir to /usr/sbin
INSTALL_RB_BINDIR =	$(USRSBINDIR)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# pass Ruby values onto the package manfiest
PKG_MACROS +=	RUBY_VERSION=$(RUBY_VERSION)
PKG_MACROS +=	RUBY_LIB_VERSION=$(RUBY_LIB_VERSION)

# common targets
build:		$(BUILD_32)

# make sure facter and hiera are installed first
install:	../facter/build/$(MACH32)/.installed ../hiera/build/$(MACH32)/.installed $(INSTALL_32)

# puppet requires the installation of the following rubygems to run
# the unittests:  rspec rspec-expectations mocha rack rgen
# Disable the tests until these rubygems are available.
test:		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += library/ruby/hiera
REQUIRED_PACKAGES += system/management/facter
