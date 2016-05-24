#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2015, Aurelien Larcher. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libwpg
COMPONENT_VERSION=	0.3.0
COMPONENT_FMRI=     	library/c++/libwpg
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/libwpg
COMPONENT_SUMMARY=      libwpg - library for importing and converting Corel WordPerfect(tm) Graphics images
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:6f709199235f4c061c3ffe1a5112ce6430e8434e621bf7b3e3dca16114eaf224
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/libwpg/files/libwpg/libwpg-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      LGPLv2.1 MPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)


