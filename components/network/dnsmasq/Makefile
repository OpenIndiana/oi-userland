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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

# i18n component requires GNU xgettext
PATH=$(PATH.gnu)

COMPONENT_NAME=		dnsmasq
COMPONENT_VERSION=	2.78
COMPONENT_PROJECT_URL=	http://www.thekelleys.org.uk
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:c92e5d78aa6353354d02aabf74590d08980bb1385d8a00b80ef9bc80430aa1dc
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/dnsmasq


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += PREFIX="/usr"
COMPONENT_BUILD_ARGS += LOCALEDIR="/usr/share/locale"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS) -m$(BITS)"
COMPONENT_BUILD_TARGETS = "all-i18n"
COMPONENT_INSTALL_ENV += CC="$(CC)"
COMPONENT_INSTALL_ARGS += CC="$(CC)"
COMPONENT_INSTALL_ARGS += PREFIX="/usr"
COMPONENT_INSTALL_ARGS += BINDIR="$(USRLIBDIR)/inet"
COMPONENT_INSTALL_TARGETS = "install-i18n"




# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)


REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += system/library
