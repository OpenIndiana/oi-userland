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

COMPONENT_NAME=		kramdown-parser-gfm
COMPONENT_VERSION=	1.0.1
COMPONENT_SUMMARY=	kramdown parser for the GFM dialect of Markdown
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:114600c19bb1a71f0f45414921eb74e4dee84010e05b59294d8dc27b9550767a
COMPONENT_ARCHIVE_URL=  https://rubygems.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://kramdown.gettalong.org/
COMPONENT_FMRI=		library/ruby/kramdown-parser-gfm
COMPONENT_CLASSIFICATION=	Development/Ruby
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
	$(GEM) spec $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) --ruby > $(SOURCE_DIR)/$(GEMSPEC)

REQUIRED_PACKAGES += runtime/ruby-23
