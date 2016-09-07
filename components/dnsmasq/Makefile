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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

# i18n component requires GNU xgettext
PATH=$(GNUBIN):$(USRBINDIR):$(USRSBINDIR)

COMPONENT_NAME=		dnsmasq
COMPONENT_VERSION=	2.75
COMPONENT_PROJECT_URL=	http://www.thekelleys.org.uk
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f8252c0a0ba162c2cd45f81140c7c17cc40a5fca2b869d1a420835b74acad294
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/dnsmasq

TPNO=			28028

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LOCALEDIR="$(USRSHARELOCALEDIR)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS) $(CC_BITS)"
COMPONENT_BUILD_TARGETS = "all-i18n"
COMPONENT_INSTALL_ENV += CC="$(CC)"
COMPONENT_INSTALL_ARGS += CC="$(CC)"
COMPONENT_INSTALL_ARGS += PREFIX="$(USRDIR)"
COMPONENT_INSTALL_ARGS += BINDIR="$(USRLIBDIR)/inet"
COMPONENT_INSTALL_TARGETS = "install-i18n"

REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += system/core-os
