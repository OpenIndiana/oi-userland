
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

COMPONENT_NAME=		facter
COMPONENT_VERSION=	2.4.6
COMPONENT_SUMMARY=	Facter - collect and display facts about the system
COMPONENT_DESCRIPTION=	The facter(8) command collects and displays facts about the current system.\
 The library behind Facter is easy to expand, making Facter an easy way\
 to collect information about a system from within the shell or within Ruby.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:56ffc5fbcd550fcdb4788bc4d7fd0199bff69937d6df1e5a1f61c92d143d78fe
COMPONENT_ARCHIVE_URL=	http://rubygems.org/gems/$(COMPONENT_SRC).gem
COMPONENT_PROJECT_URL=  http://puppetlabs.com/facter
COMPONENT_FMRI=		system/management/facter
COMPONENT_CLASSIFICATION=	Development/Ruby
COMPONENT_LICENSE=	Apache v2.0
COMPONENT_LICENSE_FILE=	facter.license

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
    $(GEM) spec $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) --ruby > $(SOURCE_DIR)/$(GEMSPEC)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/gem.mk
include $(WS_TOP)/make-rules/ruby.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

# facter requires the installation of the following rubygems to run
# the unittests:  rspec rspec-expectations mocha rake rack hiera
# Disable the tests until these rubygems are available.
test:		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/ruby-23
