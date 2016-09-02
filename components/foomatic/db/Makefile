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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		foomatic-db
DAILY_VERSION=		20160721
# foomatic-db creates only the daily snapshots
COMPONENT_VERSION=	$(DAILY_VERSION)
FOO_VERSION=		4.0
IPS_COMPONENT_VERSION=	$(FOO_VERSION).$(DAILY_VERSION)
TPNO=			30222
# version (4.0) is relative to foomatic-db-engine
#  ...do not combine foomatic-db with foomatic-db-engine of the different versions
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(FOO_VERSION)-$(DAILY_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8067ec4cee262fad8a490cb2a2836a8576eff745dd74b6478899b337a020a607
COMPONENT_ARCHIVE_URL=	http://www.openprinting.org/download/foomatic/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://wiki.linuxfoundation.org/openprinting/database/foomatic
COMPONENT_BUGDB=	utility/foomatic

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# var is needed to check the "weird symlinks"
PKG_MACROS += COMPONENT_DIR="$(COMPONENT_DIR)"
# directory to search for "include" in mogrify .p5m
PKG_OPTIONS += -I $(COMPONENT_DIR)

COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);
COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)

CONFIGURE_OPTIONS +=	--with-drivers=NOOBSOLETES
CONFIGURE_OPTIONS +=	INSTALL=/usr/sbin/install
CONFIGURE_OPTIONS +=	TAR=/usr/gnu/bin/tar

ASLR_MODE = $(ASLR_NOT_APPLICABLE)
