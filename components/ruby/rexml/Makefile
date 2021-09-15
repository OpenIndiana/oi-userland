#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 Alexander Pyhalov
#

BUILD_BITS=32
BUILD_STYLE=gem

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rexml
COMPONENT_VERSION=	3.2.5
COMPONENT_SUMMARY=	An XML toolkit for Ruby 
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:a33c3bf95fda7983ec7f05054f3a985af41dbc25a0339843bd2479e93cabb123
COMPONENT_ARCHIVE_URL=  https://rubygems.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://github.com/ruby/rexml
COMPONENT_FMRI=		library/ruby/rexml
COMPONENT_CLASSIFICATION=	Development/Ruby
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.txt

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
	$(GEM) spec $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) --ruby > $(SOURCE_DIR)/$(GEMSPEC)

REQUIRED_PACKAGES += runtime/ruby-23
