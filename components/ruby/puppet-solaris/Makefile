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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk
RUBY_VERSION=2.1
RUBY_LIB_VERSION=2.1.0
RUBY_VERSIONS=2.1.0
RUBY=/usr/ruby/$(RUBY_VERSION)/bin/ruby

COMPONENT_NAME=		puppet-solaris
COMPONENT_SRC=
COMPONENT_VERSION=	$(PKG_SOLARIS_VERSION)
COMPONENT_BUGDB=	utility/puppet

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ruby.mk
include $(WS_MAKE_RULES)/ips.mk


# Not implemented by any make rules we are loading
$(BUILD_64): ext/PuppetAudit.so $(BUILD_DIR)
	$(MKDIR) $(dir $@)
	$(TOUCH) $@

# Not implemented by any make rules we are loading
$(INSTALL_64): $(BUILD_64)
	$(TOUCH) $@

# common targets
build: $(BUILD_64)

INSTALL_DIR=$(BUILD_DIR)/prototype/$(MACH)
SECURITY_FILES=$(addprefix files/,auth_attr exec_attr prof_attr)
ETC_FILES=$(addprefix files/,user_attr)

ext/PuppetAudit.so:
	# Ruby extension for auditing
	(cd ext; $(RUBY) extconf.rb; $(GMAKE))

clean::
	@if [ -f ext/Makefile ]; then \
		(cd ext; $(GMAKE) clean; $(RM) Makefile) \
	fi

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += runtime/ruby-21
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
