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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		xmlto
COMPONENT_VERSION=	0.0.25
COMPONENT_PROJECT_URL=	https://fedorahosted.org/xmlto/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:c52b56d929e8d20fc19cd3b7ec238f8d039730c56ee311cc352e843147e3e31a
COMPONENT_ARCHIVE_URL=	 https://fedorahosted.org/releases/x/m/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/xmlto

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# These will be used by the xmlto script.
CONFIGURE_ENV += FIND="/usr/gnu/bin/find"
CONFIGURE_ENV += GETOPT="/usr/gnu/bin/getopt"
CONFIGURE_ENV += GREP="/usr/gnu/bin/grep"
CONFIGURE_ENV += TAIL="/usr/gnu/bin/tail"

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
