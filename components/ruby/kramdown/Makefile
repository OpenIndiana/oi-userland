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

COMPONENT_NAME=		kramdown
COMPONENT_VERSION=	2.3.1
COMPONENT_SUMMARY=	Ruby Markdown superset converter
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:59e938cfa42a3d6169b295727fe09c4c91d742336c8fbd1042529f4db664ab49
COMPONENT_ARCHIVE_URL=  https://rubygems.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://kramdown.gettalong.org/
COMPONENT_FMRI=		library/ruby/kramdown
COMPONENT_CLASSIFICATION=	Development/Ruby
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
	$(GEM) spec $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) --ruby > $(SOURCE_DIR)/$(GEMSPEC)

REQUIRED_PACKAGES += runtime/ruby-23
