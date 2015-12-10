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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		puppet
COMPONENT_VERSION=	3.6.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://puppetlabs.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9114c63108c58e39db84937cb8f7e1add3dcbaa08fd730f631de6a7f64a3c360
COMPONENT_ARCHIVE_URL=	https://downloads.puppetlabs.com/puppet/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/puppet

TPNO=			18128

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/install.rb.mk
include $(WS_TOP)/make-rules/ips.mk

# puppet requires facter and hiera as part of the install phase 
COMPONENT_INSTALL_ENV	+= RUBYLIB="$(COMPONENT_DIR)/../facter/build/$(MACH32)/lib:$(COMPONENT_DIR)/../hiera/build/$(MACH32)/lib"

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
install:	../facter/build/$(MACH32)/.installed ../hiera/build/$(MACH64)/.installed $(INSTALL_32)

clean::
	@if [ -f ext/Makefile ]; then \
		(cd ext; $(GMAKE) clean; $(RM) Makefile) \
	fi

# puppet requires the installation of the following rubygems to run
# the unittests:  rspec rspec-expectations mocha rack rgen
# Disable the tests until these rubygems are available.
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
