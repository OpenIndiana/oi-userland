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

# parfait fails to compile us (21334808)
export PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tar
COMPONENT_VERSION=	1.28
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/tar/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:60e4bfe0602fef34cd908d91cf638e17eeb09394d7b98c2487217dc4d3147562
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/tar/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gtar

TPNO=			23088

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

# tests (ttyemu.c) requires c99
studio_C99MODE = $(studio_C99_ENABLE)

# Enforce tar binary to standard path
CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin

# Use ssh (rather than rsh) for remote commands.
CONFIGURE_ENV += "RSH=/usr/bin/ssh"

CONFIGURE_OPTIONS +=	--with-rmt=/usr/sbin/rmt
CONFIGURE_OPTIONS +=	--libexecdir=/usr/sbin
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 

COMPONENT_SYSTEM_TEST_DIR = $(BUILD_DIR_64)/tests
COMPONENT_SYSTEM_TEST_TARGETS =  installcheck-local

# Remove everything except test output.
COMPONENT_TEST_TRANSFORMS = \
	'-e "/^\#\# ----/,/tests were skipped\./p" ' \
	'-e "/.*/d" '

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(BUILD_64) $(SYSTEM_TEST_64)


REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/gzip
REQUIRED_PACKAGES += network/ssh
REQUIRED_PACKAGES += network/openssh
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
