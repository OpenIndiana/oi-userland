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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdebug
COMPONENT_VERSION=	2.2.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
    sha256:91e426fb3e8ea2b49a1d129b0e56cf357891ea4ef7a95d9a45350d8143f593bc
COMPONENT_ARCHIVE_URL=	http://xdebug.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://xdebug.org/

PATCH_DIR = ../xdebug/patches

include ../extensions-zts.mk

CONFIGURE_OPTIONS += --enable-xdebug
