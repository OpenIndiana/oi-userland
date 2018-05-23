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

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tar
COMPONENT_VERSION=	1.30
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/tar/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:87592b86cb037c554375f5868bdd3cc57748aef38d6cb741c81065f0beac63b7
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/tar/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gtar
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

# ERROR: 195 tests were run,
# 3 failed unexpectedly: 156 175 176
# 25 tests were skipped.
test:		$(TEST_64)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/gzip
REQUIRED_PACKAGES += network/ssh
# rmt(1M)
REQUIRED_PACKAGES += service/network/network-clients
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/extended-system-utilities
REQUIRED_PACKAGES += system/library
