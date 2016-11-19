
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
# Copyright 2016 Grüninger GmbH, Andreas Grüninger (grueni)
#
include ../../../make-rules/shared-macros.mk

RUBY_VERSION = 2.2
RUBY_LIB_VERSION = 2.2.0
RUBY = $(RUBY.$(RUBY_VERSION))
RUBY_VERSIONS = $(RUBY_LIB_VERSION)

COMPONENT_NAME=           bundler
COMPONENT_VERSION=        1.13.6
COMPONENT_FMRI=           library/ruby/$(COMPONENT_NAME)
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=   sha256:fafd22dfed658ca0603f321bdd168ed709d7c682e61273b55637716459f2d0f7
COMPONENT_ARCHIVE_URL=    http://rubygems.org/gems/$(COMPONENT_SRC).gem
COMPONENT_PROJECT_URL=    http://puppetlabs.com/bundler
COMPONENT_CLASSIFICATION= Development/Ruby
COMPONENT_LICENSE=        MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/gem.mk

# gemspec in the gem is incomplete. Create one with the content of archive
COMPONENT_POST_UNPACK_ACTION= \
    $(GEM) spec --ruby $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) > $(SOURCE_DIR)/$(GEMSPEC)

# common targets
build:    $(BUILD_32)

install:  $(INSTALL_32)

test:     $(TESTS_32)


REQUIRED_PACKAGES += runtime/ruby-22
