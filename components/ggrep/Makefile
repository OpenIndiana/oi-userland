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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		grep
COMPONENT_VERSION=	2.10
COMPONENT_PROJECT_URL=	http://gnu.org/software/grep/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2

# Note that the 2.10 version of the compressed GNU grep tarball on
# ftp.gnu.org is only available in .xz format. We cannot use this
# as xz is not currently part of the Solaris 11 Update CBE. We 
# have recompressed that tarball as a .bz2 file and placed it in the
# special Userland cache. The sha256 hash is for the payload .tar file.
COMPONENT_ARCHIVE_HASH=	\
    sha256:299d0ccb0238894cc674da3c5a6a6fb82c3d63286f7f127e448e2ff97d21e2fb
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/grep/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# We need to be able to return from void functions
CFLAGS	+=			$(studio_FEATURES_EXTENSIONS)

CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		--prefix=/usr

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
