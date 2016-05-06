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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pconsole
COMPONENT_VERSION=	1.0
COMPONENT_PROJECT_URL=	http://www.heiho.net/pconsole/
COMPONENT_ARCHIVE_HASH=	\
    sha256:94520bf65f726df9d7e686bb486e9a2828c29d09a20b9522f1da4f7d66700bb2
COMPONENT_ARCHIVE_URL=	http://www.heiho.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

TPNO=			9270

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Required to configure correctly.
COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

# -I argument needed to find the generated config.h file.  Also, pconsole
# configure.in forcibly overrides CFLAGS, so we override the compiler to
# specify required flags.
CONFIGURE_ENV += "CC=$(CC) -I. $(CC_BITS)"

REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += text/gawk
