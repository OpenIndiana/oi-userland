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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		puppet
COMPONENT_VERSION=	3.2.2
COMPONENT_PROJECT_URL=	http://puppetlabs.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c47745aa73912b2cb1a20b07e8741b8af37a920b9bc8dc8afb14b23d8df7d13d
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)downloads/puppet/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/puppet

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/install.rb.mk
include $(WS_TOP)/make-rules/ips.mk

# puppet requires facter to build
COMPONENT_INSTALL_ENV	+= RUBYLIB="$(COMPONENT_DIR)/../facter/build/prototype/$(MACH)$(VENDOR_RUBY)"

../facter/build/%/.installed:
	(cd ../facter ; $(GMAKE) install)

# set the bindir to /usr/sbin
INSTALL_RB_BINDIR =	$(USRSBINDIR)

# common targets
build:		$(BUILD_32)

# make sure facter is installed first
install:	../facter/build/$(MACH32)/.installed $(INSTALL_32)

# puppet requires the installation of the following rubygems to run
# the unittests:  rspec rspec-expectations mocha rake rack hiera rgen
# Disable the tests until these rubygems are available.
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
