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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tar
COMPONENT_VERSION=	1.32
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/tar/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:d0d3ae07f103323be809bc3eac0dcc386d52c5262499fe05511ac4788af1fdd8
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/tar/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		archiver/gnu-tar

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Use ssh (rather than rsh) for remote commands.
CONFIGURE_ENV += "RSH=/usr/bin/ssh"

CONFIGURE_OPTIONS +=	--with-rmt=/usr/sbin/rmt
CONFIGURE_OPTIONS +=	--libexecdir=/usr/sbin

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# rmt(1M)
REQUIRED_PACKAGES += service/network/network-clients
REQUIRED_PACKAGES += SUNWcs
# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/gzip
REQUIRED_PACKAGES += network/ssh
REQUIRED_PACKAGES += system/extended-system-utilities
REQUIRED_PACKAGES += system/library
