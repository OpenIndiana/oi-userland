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
# Copyright (c) 2015-2017 Aurelien Larcher. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsamplerate
COMPONENT_VERSION=	0.1.9
COMPONENT_FMRI=	library/libsamplerate
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SUMMARY=	Secret Rabbit Code (aka libsamplerate) - Sample Rate Converter for audio 
COMPONENT_PROJECT_URL=	http://www.mega-nerd.com/SRC/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0a7eb168e2f21353fb6d84da152e4512126f7dc48ccb0be80578c565413444c1
COMPONENT_ARCHIVE_URL=	http://www.mega-nerd.com/SRC/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD	

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--enable-shared

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
