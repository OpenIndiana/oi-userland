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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtecla
COMPONENT_VERSION=	1.6.1
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_PROJECT_URL=	http://www.astro.caltech.edu/~mcs/tecla/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:21db2947bd1415070e0462673aa9bed04610946e09169fcd63e02557b0d999a1
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

# Userland default includes -mt which links with libthread which we don't need.
studio_MT =

# This is needed for the 64-bit library to be built correctly.
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"

# We have our own pre-Solarified man pages.
CONFIGURE_OPTIONS +=	--without-man-pages

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:	$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

include ../../make-rules/depend.mk
