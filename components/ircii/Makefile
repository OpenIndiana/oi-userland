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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ircii
COMPONENT_VERSION=	20060725
IPS_COMPONENT_VERSION=  0.2006.7.25
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:421996726cd06b6659857b8e61195d614a68d8c6
COMPONENT_ARCHIVE_URL=	ftp://ircii.warped.com/pub/ircII/old/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_ENV += CC="$(CC)"

# We need to reset configure options here because ircii is confused with
# CC and CFLAGS definitions as configure parameters.
CONFIGURE_OPTIONS       = --prefix=/usr
CONFIGURE_OPTIONS       += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS       += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS       += $(CONFIGURE_OPTIONS.$(BITS))


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
