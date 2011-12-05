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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		foomatic-db
COMPONENT_VERSION=	20080903
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:fe0fa874a4556dd32fb803b613a47f7c13076184
COMPONENT_ARCHIVE_URL=	$(EXTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.linuxfoundation.org/collaborate/workgroups/openprinting/database/foomatic/

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)

# One file is not gzipped; fix it
COMPONENT_POST_INSTALL_ACTION = \
 gzip -c $(SOURCE_DIR)/db/source/PPD/Oce/Others/IM8530_1.PPD \
  > $(PROTO_DIR)/usr/share/foomatic/db/source/PPD/Oce/Others/IM8530_1.ppd.gz

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
