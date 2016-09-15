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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_dtrace
COMPONENT_VERSION=	0.3.1
COMPONENT_SRC=		src
COMPONENT_ARCHIVE=
COMPONENT_ARCHIVE_SRC=	none
COMPONENT_PROJECT_URL=	http://prefetch.net/projects/apache_modtrace/

TPNO=			8876

BUILD_STYLE= justmake
MODULES_INSTALL=
include ../modules.mk

COMPONENT_BUILD_ARGS +=	APXS=$(APXS)
COMPONENT_BUILD_ARGS +=	DTRACE="$(USRSBINDIR)/dtrace -$(BITS)"
COMPONENT_BUILD_ARGS +=	PATH="$(PATH)"

CLEAN_PATHS += $(SOURCE_DIR)/.prep
