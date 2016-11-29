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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

# Puppet modules do not have any concept of 'build' so make this a no-op
$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

# Modify ruby scripts containing "#!/usr/bin/env ruby" to
# use the version-specific ruby path, defined by the $(RUBY_VERSION) macro.
# Without this change, the mediated ruby version in /usr/bin/ruby
# will probably be used, which may not match the ruby
# version supported by the puppet module.
COMPONENT_POST_INSTALL_ACTION += \
    cd $(PROTO_DIR); \
    $(RUBY_SCRIPT_FIX_FUNC);

# install the source into the proto directory
$(BUILD_DIR)/%/.installed:      $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(SOURCE_DIR); \
		$(MKDIR) -p $(PROTO_DIR)/usr/puppetlabs/puppet/modules/$(MODULE_NAME); \
		$(CP) -R * $(PROTO_DIR)/usr/puppetlabs/puppet/modules/$(MODULE_NAME))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

REQUIRED_PACKAGES += system/management/puppet
