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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tar
COMPONENT_VERSION=	1.28
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/tar/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:60e4bfe0602fef34cd908d91cf638e17eeb09394d7b98c2487217dc4d3147562
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/tar/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gtar

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATCH_LEVEL=0

# workaround for CR 6998994
# sparc_COPTFLAG = -xO2

# Use ssh (rather than rsh) for remote commands.
CONFIGURE_ENV += "RSH=/usr/bin/ssh"

CONFIGURE_OPTIONS +=	--with-rmt=/usr/sbin/rmt
CONFIGURE_OPTIONS +=	--libexecdir=/usr/sbin

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Failed tests: 
#25: terminal input FAILED (iotty.at:29)
#87: incremental dump when the parent directory is unreadable FAILED (listed03.at:27)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/gzip
REQUIRED_PACKAGES += network/ssh
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/extended-system-utilities
REQUIRED_PACKAGES += system/library
