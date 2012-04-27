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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdebug
COMPONENT_VERSION=	2.0.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4638641e643f4cedd9d2ec360fb13f47221973518b07ec6a2016c967063bb8b2
COMPONENT_ARCHIVE_URL=	http://xdebug.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://xdebug.org/

include ../extensions.mk

CONFIGURE_OPTIONS += --enable-xdebug

COMPONENT_POST_INSTALL_ACTION = ( \
	$(FIX_CONFIG_FILES); \
	)

PKG_PROTO_DIRS += $(COMPONENT_DIR)/../xdebug-zts/build/prototype/$(MACH)
