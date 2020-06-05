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

#
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
GEM=/usr/ruby/$(RUBY_VERSION)/bin/gem

VENDOR_GEM_DIR=/usr/ruby/$(RUBY_VERSION)/lib/ruby/vendor_ruby/gems/$(RUBY_LIB_VERSION)

# Name of the gem spec to use.  This will typically be
# <component_name>.gemspec
GEMSPEC=$(COMPONENT_NAME).gemspec


# Some gems projects have to be built using rake
# Allow GEM build/install commands to be overwritten
# to account for possible differences
GEM_BUILD_ACTION=(cd $(@D); $(GEM) build $(GEM_BUILD_ARGS) $(GEMSPEC))

# Build install args in a more readable fashion
ifeq ($(firstword $(subst .,$(space),$(RUBY_VERSION))),2)
# gem install 2.x does docs differently. Continue to generate both types
GEM_INSTALL_ARGS += --document rdoc,ri
endif

GEM_INSTALL_ARGS += -V --local --force
GEM_INSTALL_ARGS += --install-dir $(PROTO_DIR)/$(VENDOR_GEM_DIR)
GEM_INSTALL_ARGS += --bindir $(PROTO_DIR)/$(VENDOR_GEM_DIR)/bin

# cd into build directory
# gem 2.2.3 uses .gem from the cwd ignoring command line .gem file
# gem 1.8.23.2 uses command line .gem file OR .gem from cwd
GEM_INSTALL_ACTION= (cd $(@D); $(GEM) install $(GEM_INSTALL_ARGS) $(COMPONENT_NAME))


$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(GTAR) -C $(SOURCE_DIR) -cpf - . | $(GTAR) -C $(@D) -xpf -
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

COMPONENT_TEST_TARGETS =

# Test the built source.  If the output file shows up in the environment or
# arguments, don't redirect stdout/stderr to it.
$(BUILD_DIR)/%/.tested-and-compared:    $(BUILD_DIR)/%/.built
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	-(cd $(COMPONENT_TEST_DIR) ; \
	    $(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
	    $(COMPONENT_TEST_CMD) \
	    $(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS)) \
	    $(if $(findstring $(COMPONENT_TEST_OUTPUT),$(COMPONENT_TEST_ENV)$(COMPONENT_TEST_ARGS)),,&> $(COMPONENT_TEST_OUTPUT))
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@


$(BUILD_DIR)/%/.tested:    $(COMPONENT_TEST_DEP)
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR) ; \
	    $(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
	    $(COMPONENT_TEST_CMD) \
	    $(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS))
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)

USERLAND_REQUIRED_PACKAGES += runtime/ruby
