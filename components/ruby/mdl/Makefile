# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mdl
COMPONENT_VERSION=	0.4.0
COMPONENT_SUMMARY=	Markdown lint tool
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:e2de244a72ac4e90bd9045582fe7cfed84b436342a127dd6a5fb9c2b016fa637
COMPONENT_ARCHIVE_URL=	http://rubygems.org/gems/$(COMPONENT_SRC).gem
COMPONENT_PROJECT_URL=  https://github.com/markdownlint/markdownlint
COMPONENT_FMRI=		developer/documentation-tool/mdl
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE.txt

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
    $(GEM) spec $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) --ruby > $(SOURCE_DIR)/$(GEMSPEC)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/gem.mk
include $(WS_MAKE_RULES)/ruby.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += runtime/ruby-23
