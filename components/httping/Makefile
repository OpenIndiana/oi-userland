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

COMPONENT_NAME=		httping
COMPONENT_VERSION=	1.5.8
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.vanheusden.com/httping/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f4c1d216349d308f5d5cfe2840ee4fe75b767bf76b49ba3dc140be55db5947bf
COMPONENT_ARCHIVE_URL=	http://critical.ch/distfiles/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/httping

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

CC +=		$(CC_BITS)

# Override the values in the Makefile but get optimization level etc. from 
# make-rules/shared-macros.mk.
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS) -DVERSION=\\\"$(COMPONENT_VERSION)\\\""
COMPONENT_BUILD_ARGS += WFLAGS=""
COMPONENT_BUILD_ARGS +=	LDFLAGS="$(LDFLAGS) -lsocket -lnsl -lssl -lcrypto"
COMPONENT_BUILD_ENV += CC="$(CC)"

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
