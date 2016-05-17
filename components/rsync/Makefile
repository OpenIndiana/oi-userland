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
# Copyright (c) 2009, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rsync
COMPONENT_VERSION=	3.1.2
COMPONENT_PROJECT_URL=	http://rsync.samba.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:ecfa62a7fa3c4c18b9eccd8c16eaddee4bd308a76ea50b5c02a5840f09c0a1c2
COMPONENT_ARCHIVE_URL=	http://rsync.samba.org/ftp/rsync/src/$(COMPONENT_ARCHIVE)

TPNO=			28346

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=		SHELL_PATH=$(BINDIR)/sh
CONFIGURE_OPTIONS  +=		--with-included-popt
CONFIGURE_OPTIONS  +=		--enable-xattr-support
