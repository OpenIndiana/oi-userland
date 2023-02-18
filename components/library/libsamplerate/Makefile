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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsamplerate
COMPONENT_VERSION=	0.2.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=	Secret Rabbit Code (aka libsamplerate) - Sample Rate Converter for audio 
COMPONENT_PROJECT_URL=	https://libsndfile.github.io/libsamplerate/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/libsndfile/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:16e881487f184250deb4fcb60432d7556ab12cb58caea71ef23960aec6c0405a
COMPONENT_FMRI=	library/libsamplerate
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	BSD	
COMPONENT_LICENSE_FILE=	COPYING	

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION=  ( cd $(@D) && NOCONFIGURE=1 ./autogen.sh )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

COMPONENT_TEST_TRANSFORMS += \
	'-n' \
	'-e "/Pass/p"' \
	'-e "/PASS/p"' \
	'-e "/ok/p"' \
	'-e "/passed/p"' \
	'-e "/======/p"'

# Manually added dependencies
REQUIRED_PACKAGES += library/libsndfile

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
