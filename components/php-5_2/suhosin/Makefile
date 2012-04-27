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

COMPONENT_NAME=		suhosin
COMPONENT_VERSION=	0.9.29
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3ac3a7d2ea5dc27189fadb7945da0caf18fe22c87369404bc32d7cf80ae95379
COMPONENT_ARCHIVE_URL=	http://download.suhosin.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.hardened-php.net/suhosin/index.html

include ../extensions.mk

CONFIGURE_OPTIONS  += --enable-suhosin

COMPONENT_POST_INSTALL_ACTION = ( \
	$(FIX_CONFIG_FILES); \
	)

PKG_PROTO_DIRS += $(COMPONENT_DIR)/../suhosin-zts/build/prototype/$(MACH)
