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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2023, Friedrich Kink
#

BUILD_BITS=	64_and_32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libnet
COMPONENT_VERSION=	1.2
COMPONENT_SUMMARY=	libnet - a library for portable network packet construction
COMPONENT_DESCRIPTION=	the libnet network packet construction library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://github.com/libnet/libnet
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:caa4868157d9e5f32e9c7eac9461efeff30cb28357f7f6bf07e73933fb4edaa7
COMPONENT_ARCHIVE_URL=	https://github.com/libnet/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/library/libnet
COMPONENT_BUGDB=	library/libnet
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-doxygen-html
CONFIGURE_OPTIONS += --enable-doxygen-pdf

test:		$(NO_TESTS)
# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
