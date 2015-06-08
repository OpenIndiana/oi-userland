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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		liblogging
COMPONENT_VERSION=	1.0.4
COMPONENT_PROJECT_URL=	http://www.liblogging.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:aceb5d2aa8bdc771ff66f407f9adf4176b654db63e34a8605795b68be537b81c
COMPONENT_ARCHIVE_URL=	\
    http://download.rsyslog.com/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rsyslog
TPNO=			20535

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Means build only stdlog
CONFIGURE_OPTIONS +=    --disable-journal

# There are built man pages in the tarball, which we shall patch. Making them
# here would require python-docutils.
CONFIGURE_OPTIONS +=	--disable-man-pages
CONFIGURE_OPTIONS +=    --bindir=$(USRBINDIR)

# Set -m32 or -m64 correctly for 32 and 64 bit versions.
CC +=	$(CC_BITS)

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

REQUIRED_PACKAGES += system/library
