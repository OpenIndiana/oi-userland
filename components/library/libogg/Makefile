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
# Copyright (c) 2013 David Hoeppner. All rights reserved.
#

BUILD_BITS=				32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libogg
COMPONENT_VERSION=      1.3.5
COMPONENT_FMRI=         library/libogg
COMPONENT_SUMMARY=      libogg - general-purpose compressed audio format
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=  https://xiph.org/ogg
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0eb4b4b9420a0f51db142ba3f9c64b333f826532dc0f48c6410ae51f4799b664
COMPONENT_ARCHIVE_URL=	http://downloads.xiph.org/releases/ogg/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--enable-shared

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += '-n -e "/ok.$$/p" '

# Setup config_types.h file to support 32 & 64 bit.
COMPONENT_POST_INSTALL_ACTION= \
            (cd $(PROTOUSRDIR) ;  \
             $(MV) include/ogg/config_types.h include/ogg/config_types-$(BITS).h )

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
