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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#

VENDOR_RUBY = /usr/ruby/$(RUBY_VERSION)/lib/ruby/vendor_ruby/$(RUBY_LIB_VERSION)

# default user executable binaries to /usr/bin
INSTALL_RB_BINDIR =	$(USRBINDIR)

# install.rb scripts do not have any concept of 'build' so make this a
# no-op
$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

# install the source into the proto directory
$(BUILD_DIR)/%/.installed:      $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(SOURCE_DIR) ; $(ENV) $(COMPONENT_INSTALL_ENV) \
                ./install.rb --destdir=$(PROTO_DIR) \
                --ruby=$(RUBY) \
                --bindir=$(INSTALL_RB_BINDIR) \
                --sitelibdir=$(VENDOR_RUBY) \
                --mandir=$(USRSHAREMANDIR))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

clean::
	$(RM) -r $(SOURCE_DIR) $(BUILD_DIR)
