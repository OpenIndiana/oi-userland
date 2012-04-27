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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		httping
COMPONENT_VERSION=	1.4.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.vanheusden.com/httping/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f00da30e0744d86ed832f6a49ae455b9447570af3589e1111a1c6210a51cafee
COMPONENT_ARCHIVE_URL=	http://www.vanheusden.com/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPONENT_BUILD_ARGS +=	CFLAGS="$(CFLAGS) -Dstrndup=strndup -DVERSION=\\\"$(COMPONENT_VERSION)\\\""
COMPONENT_BUILD_ARGS +=	LDFLAGS="$(LDFLAGS) -lsocket -lnsl -lssl -lcrypto"
COMPONENT_BUILD_ENV += CC="$(CC)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:	$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
