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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libedit
COMPONENT_VERSION=	20170329-3.1
IPS_COMPONENT_VERSION=  3.1
COMPONENT_SUMMARY=	Libedit - Command line editor library
COMPONENT_PROJECT_URL=	http://www.thrysoee.dk/editline/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:91f2d90fbd2a048ff6dad7131d9a39e690fd8a8fd982a353f1333dd4017dd4be
COMPONENT_ARCHIVE_URL=	http://www.thrysoee.dk/editline/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_FMRI=	library/libedit
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	BSD

# Uses GNU awk
PATH=$(PATH.gnu)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -f)

CONFIGURE_OPTIONS +=   --enable-shared
CONFIGURE_OPTIONS +=   --disable-static
CONFIGURE_OPTIONS +=   --enable-widec


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)


# Build dependencies
REQUIRED_PACKAGES += text/gawk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
