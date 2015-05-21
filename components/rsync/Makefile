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
# Copyright (c) 2009, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rsync
COMPONENT_VERSION=	3.1.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://rsync.samba.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7de4364fcf5fe42f3bdb514417f1c40d10bbca896abe7e7f2c581c6ea08a2621
COMPONENT_ARCHIVE_URL=	http://rsync.samba.org/ftp/rsync/src/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/rsync

TPNO=			21574

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		SHELL_PATH=/bin/sh
CONFIGURE_OPTIONS  +=		--bindir=$(CONFIGURE_BINDIR.32)
CONFIGURE_OPTIONS  +=		--with-included-popt
CONFIGURE_OPTIONS  +=		--enable-xattr-support

# Enable ASLR for this component
ASLR_MODE =	$(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += system/library
