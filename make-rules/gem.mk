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
GEM_BUILD_ACTION=cd $(@D); $(GEM) build $(GEM_BUILD_ARGS) $(GEMSPEC);

define ruby-extension-rule
GEM_BUILD_ACTION += cd $(@D); $(RUBY) -Cext/$(1) extconf.rb --vendor
GEM_BUILD_ACTION += cd $(@D); $(MAKE) -Cext/$(1)
endef

ifneq ($(strip $(RUBY_EXTENSIONS)),)
GEM_BUILD_ACTION += cd $(@D); for extension in $(RUBY_EXTENSIONS); do $(RUBY) -C $${extension%/*} $${extension\#\#*/} --vendor; done;
GEM_BUILD_ACTION += cd $(@D); for extension in $(RUBY_EXTENSIONS); do $(MAKE) -C $${extension%/*}; done
endif

define ruby-rule
$(BUILD_DIR)/%-$(1)/.built:             RUBY_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.built:             RUBY_LIB_VERSION=$(RUBY_LIB_VERSION.$(1))
$(BUILD_DIR)/%-$(1)/.installed:         RUBY_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.installed:         RUBY_LIB_VERSION=$(RUBY_LIB_VERSION.$(1))
$(BUILD_DIR)/%-$(1)/.tested:            RUBY_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.tested:            RUBY_LIB_VERSION=$(RUBY_LIB_VERSION.$(1))
$(BUILD_DIR)/%-$(1)/.tested-and-compared:       RUBY_VERSION=$(1)
$(BUILD_DIR)/%-$(1)/.tested-and-compared:       RUBY_LIB_VERSION=$(RUBY_LIB_VERSION.$(1))
endef

$(foreach rbver, $(RUBY_VERSIONS), $(eval $(call ruby-rule,$(rbver))))

$(BUILD_DIR)/$(MACH32)-%/.built:        BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:        BITS=64
$(BUILD_DIR)/$(MACH32)-%/.installed:    BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:    BITS=64
$(BUILD_DIR)/$(MACH32)-%/.tested:       BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested:       BITS=64
$(BUILD_DIR)/$(MACH32)-%/.tested-and-compared:  BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared:  BITS=64

BUILD_32 = $(RUBY_32_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.built)
BUILD_64 = $(RUBY_64_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
BUILD_NO_ARCH = $(RUBY_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.built)

ifeq ($(filter-out $(RUBY_64_ONLY_VERSIONS), $(RUBY_VERSION)),)
BUILD_32_and_64 = $(BUILD_64)
endif

ifeq ($(filter-out $(RUBY_32_ONLY_VERSIONS), $(RUBY_VERSION)),)
BUILD_32_and_64 = $(BUILD_32)
endif

INSTALL_32 = $(RUBY_32_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.installed)
INSTALL_64 = $(RUBY_64_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)
INSTALL_NO_ARCH = $(RUBY_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.installed)

# If we are building Ruby 2.6 support, build it and install it
# before Ruby 2.3, so 2.3 is installed last and is the canonical version.
# When we change the default, the new default should go last.
ifneq ($(findstring 2.6,$(RUBY_VERSIONS)),)
$(BUILD_DIR)/%-2.3/.built:     $(BUILD_DIR)/%-2.6/.built
$(BUILD_DIR)/%-2.3/.installed: $(BUILD_DIR)/%-2.6/.installed
endif

ifeq ($(strip $(RUBY_BUILD_DOCS)),yes)
# Build install args in a more readable fashion
ifeq ($(firstword $(subst .,$(space),$(RUBY_VERSION))),2)
# gem install 2.x does docs differently. Continue to generate both types
GEM_INSTALL_ARGS += --document rdoc,ri
endif
else
GEM_INSTALL_ARGS += --no-document
endif

GEM_INSTALL_ARGS += -V --local --force
GEM_INSTALL_ARGS += --install-dir $(PROTO_DIR)/$(VENDOR_GEM_DIR)
GEM_INSTALL_ARGS += --bindir $(PROTO_DIR)/$(VENDOR_GEM_DIR)/bin

# cd into build directory
# gem 2.2.3 uses .gem from the cwd ignoring command line .gem file
# gem 1.8.23.2 uses command line .gem file OR .gem from cwd
GEM_INSTALL_ACTION= cd $(@D); $(GEM) install $(GEM_INSTALL_ARGS) $(COMPONENT_NAME);
ifneq ($(strip $(RUBY_EXTENSIONS)),)
GEM_INSTALL_ACTION += cd $(@D); for extension in $(RUBY_EXTENSIONS); do \
	$(MAKE) -C $${extension%/*} DESTDIR=$(PROTO_DIR) install; \
	done
endif


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

# determine the type of tests we want to run.
ifeq ($(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_32 = $(RUBY_32_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.tested)
TEST_64 = $(RUBY_64_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested)
TEST_NO_ARCH = $(RUBY_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.tested)
else
TEST_32 = $(RUBY_32_VERSIONS:%=$(BUILD_DIR)/$(MACH32)-%/.tested-and-compared)
TEST_64 = $(RUBY_64_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared)
TEST_NO_ARCH = $(RUBY_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%/.tested-and-compared)
endif

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
