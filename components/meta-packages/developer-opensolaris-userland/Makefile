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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		developer/opensolaris/userland
COMPONENT_VERSION=
COMPONENT_SRC=
COMPONENT_ARCHIVE=
COMPONENT_PROJECT_URL=	https://github.com/oracle/solaris-userland
COMPONENT_ARCHIVE_URL=	https://github.com/oracle/solaris-userland.git
COMPONENT_BUGDB=	gate-stuff/userland

include $(WS_MAKE_RULES)/prep.mk

# This has a dependency on every REQUIRED_PACKAGE in Userland, some of which
# are not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/ips.mk

$(WS_MACH)/requires.mk:
	(cd $(WS_COMPONENTS) ; $(GMAKE) $@)

-include $(WS_MACH)/requires.mk

# The package is created in two parts: the checked-in manifest and a generated
# file of actions based on the REQUIRED_PACKAGES macro value.
PKG_OPTIONS += -I $(BUILD_DIR)

$(BUILD_DIR)/package.list:	$(BUILD_DIR) $(WS_MACH)/requires.mk
	@echo $(REQUIRED_PACKAGES:%="depend type=require fmri=pkg:/%\\n") >$@

build install: $(BUILD_DIR)/package.list

test:	$(NO_TESTS)

system-test:    $(NO_TESTS)

clean clobber::
	$(RM) -r $(BUILD_DIR)
