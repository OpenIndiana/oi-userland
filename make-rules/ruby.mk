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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

# This is only useful for a single ruby version substtution NOT using
# -RUBYVER and -GENFRAG manifests

# Transform file paths for ruby version without creating version specific
# packages
PKG_MACROS += RUBY_VERSION=$(RUBY_VERSION)
PKG_MACROS += RUBY_LIB_VERSION=$(RUBY_LIB_VERSION)
PKG_MACROS += RUBYV=$(subst .,,$(RUBY_VERSION))
VENDOR_RUBY = /usr/ruby/$(RUBY_VERSION)/lib/ruby/vendor_ruby/$(RUBY_LIB_VERSION)
VENDOR_RUBY_ARCH = /usr/ruby/$(RUBY_VERSION)/lib/ruby/vendor_ruby/$(RUBY_LIB_VERSION)/$(MACH64)-solaris$(SOLARIS_VERSION)

# Modify ruby scripts in the ruby-version-specific path of the proto area,
# under usr/ruby/$(RUBY_VERSION), containing "#!/usr/bin/env ruby" to
# use the version-specific ruby path, defined by the $(RUBY_VERSION) macro.
# Without this change, the mediated ruby version in /usr/bin/ruby
# will probably be used, which may not match the ruby
# version supported by the component.
COMPONENT_POST_INSTALL_ACTION += \
    cd $(PROTO_DIR)/usr/ruby/$(RUBY_VERSION); \
    $(RUBY_SCRIPT_FIX_FUNC);
