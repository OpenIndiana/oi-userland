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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ftp-proxy
COMPONENT_VERSION=	OPENBSD_5_5
IPS_COMPONENT_VERSION=	5.5
COMPONENT_PROJECT_URL=	http://www.openbsd.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
# The archive exists only in the userland cache.  In order to update the cache,
# we have to get the sources via CVS manually and ask the gatekeepers to add it.
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=
COMPONENT_ARCHIVE_SRC=	cache
COMPONENT_ARCHIVE_HASH= sha256:372dbe0ca8c6b090842a9f0fbdd13b320dc37883137d3dc674d588448aa2d5e9
COMPONENT_BUGDB=	service/ftp-proxy

TPNO=	24255

# Depends on S12-only changes in ON.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

#
# Don't overwrite CFLAGS here, just add our options there.
#
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS) -D_SOLARIS_ -DOBSD_COMP -lscf"

COMPONENT_INSTALL_ARGS +=	PREFIX=$(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS +=	MANDIR=$(PROTOUSRSHAREMANDIR)
COMPONENT_INSTALL_ARGS +=	INSTALL=$(INSTALL)

REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += network/firewall
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/header
