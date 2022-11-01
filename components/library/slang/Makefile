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
#

BUILD_BITS= 64_and_32
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		slang
COMPONENT_VERSION=	2.3.3
COMPONENT_SUMMARY=	S-Lang is a multi-platform programmer's library designed to allow a developer to create robust multi-platform software
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:f9145054ae131973c61208ea82486d5dd10e3c5cdad23b7c4a0617743c8f5a18
COMPONENT_ARCHIVE_URL=	https://www.jedsoft.org/releases/slang/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.jedsoft.org/slang/
COMPONENT_FMRI=			library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D)/autoconf && autoconf -f -o ../configure )

COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)
CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/slsh

COMPONENT_BUILD_ARGS=

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/Running /p" ' \
	'-e "/Testing /p" ' \
	'-e "/^Ok/p" ' \
	'-e "/All /p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/oniguruma
