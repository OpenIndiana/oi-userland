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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pv
COMPONENT_VERSION=	1.8.12
COMPONENT_SUMMARY=	pv is a terminal-based tool for monitoring the progress of data through a pipeline
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.ivarch.com/programs/pv.shtml
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:9687f9deedb09d0dc00d80c30691f0c91282c0d5d8fa7d6a2a085c8742c2cd7c
COMPONENT_ARCHIVE_URL=	https://www.ivarch.com/programs/sources/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		shell/pipe-viewer
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	GPLv3+
COMPONENT_LICENSE_FILE=	docs/COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

ASLR_MODE= $(ASLR_ENABLE)

CFLAGS += $(XPG6MODE)

# Note that we have 3 failing tests regarding memory safety. These tests are using valgrind which might probably lead to errors.
COMPONENT_TEST_ENV += PATH="$(PATH.gnu)"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
