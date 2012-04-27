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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pconsole
COMPONENT_VERSION=	1.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	http://www.heiho.net/pconsole/
COMPONENT_ARCHIVE_HASH=	\
    sha256:94520bf65f726df9d7e686bb486e9a2828c29d09a20b9522f1da4f7d66700bb2
COMPONENT_ARCHIVE_URL=	http://www.heiho.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Required to configure correctly.
COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# -I argument needed to find the generated config.h file.
CONFIGURE_ENV += "CC=$(CC) -I."

# If the configure options are not explicitly set, then configure fails with:
# configure: warning: CC=/ws/onnv-tools/SUNWspro/sunstudio12.1/bin/cc: invalid host type
# configure: warning: CXX=/ws/onnv-tools/SUNWspro/sunstudio12.1/bin/CC: invalid host type
# configure: error: can only configure for one host and one target at a time
CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)

# DESTDIR doesn't work correctly, so we specify some of the paths directly.
COMPONENT_INSTALL_ARGS +=	prefix=$(PROTOUSRDIR)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
