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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#
GEM=/usr/ruby/$(RUBY_VERSION)/bin/gem

VENDOR_GEM_DIR=/usr/ruby/$(RUBY_VERSION)/lib/ruby/vendor_ruby/gems/$(RUBY_LIB_VERSION)

# Name of the gem spec to use.  This will typically be
# <component_name>.gemspec
GEMSPEC=$(COMPONENT_NAME).gemspec


# Some gems projects have to be built using rake
# Allow GEM build/install commands to be overwritten
# to account for possible differences
GEM_BUILD_ACTION=(cd $(@D); $(GEM) build $(GEMSPEC))

GEM_INSTALL_ACTION=\
	$(GEM) install -V --local --install-dir $(PROTO_DIR)/$(VENDOR_GEM_DIR) \
	     --bindir $(PROTO_DIR)/$(VENDOR_GEM_DIR)/bin --force \
	     $(@D)/$(COMPONENT_ARCHIVE)

$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	# Build the gem and cause the generation of a new gem spec
	# file in $(COMPONENT_SRC)
	$(GEM_BUILD_ACTION)
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed:      $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	$(MKDIR) $(PROTO_DIR)/$(GEM_DIR)
	# Install the new recreated gem
	$(GEM_INSTALL_ACTION)
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)
