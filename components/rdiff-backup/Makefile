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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rdiff-backup
COMPONENT_VERSION=	1.3.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ee030ce638df0eb1047cf72578e0de15d9a3ee9ab24da2dc0023e2978be30c06
COMPONENT_ARCHIVE_URL=	http://download.savannah.gnu.org/releases/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.nongnu.org/rdiff-backup/
COMPONENT_BUGDB=	utility/rdiff-backup

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/setup.py.mk

# Needed to get around a broken /usr/lib/python2.7/config/Makefile
# See CR #16837431.
LD=$(CC)
LDSHARED=$(CC) -G $(CC_BITS)
CFLAGS= $(CC_BITS)
CPPFLAGS=
LDFLAGS=
PYTHON_ENV += CC="$(CC)"
PYTHON_ENV += LDSHARED="$(LDSHARED)"
PYTHON_ENV += LD="$(LD)"
PYTHON_ENV += CFLAGS="$(CFLAGS)"
PYTHON_ENV += CPPFLAGS="$(CPPFLAGS)"
PYTHON_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_INSTALL_ENV += $(PYTHON_ENV)

# common targets

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
