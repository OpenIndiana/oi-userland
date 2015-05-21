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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		automake
COMPONENT_VERSION=	1.15
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7946e945a96e28152ba5a6beb0625ca715c6e32ac55f2e353ef54def0c8ed924
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/automake/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/automake

TPNO=			21310

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=	--infodir=/usr/share/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/info
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=	PERL="$(PERL)"

COMPONENT_TEST_ENV +=	-i PATH=$(GCC_ROOT)/bin:/usr/gnu/bin:/usr/bin

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
configure:	$(CONFIGURE_NO_ARCH)

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
