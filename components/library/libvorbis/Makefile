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
# Copyright (c) David Hoeppner. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvorbis
COMPONENT_VERSION=	1.3.6
COMPONENT_REVISION= 1
COMPONENT_FMRI=		library/libvorbis
COMPONENT_CLASSIFICATION=		System/Libraries
COMPONENT_SUMMARY=		libvorbis - general-purpose compressed audio format
COMPONENT_PROJECT_URL=	http://xiph.org/vorbis/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:6ed40e0241089a42c48604dc00e362beee00036af2d8b3f46338031c9e0351cb
COMPONENT_ARCHIVE_URL=\
  http://downloads.xiph.org/releases/vorbis/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--disable-docs
CONFIGURE_OPTIONS  +=		--enable-shared

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
