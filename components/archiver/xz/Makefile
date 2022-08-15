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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS=			64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xz
COMPONENT_VERSION=	5.2.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://tukaani.org/xz/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a2105abee17bcd2ebd15ced31b4f5eda6e17efd6b10f921a01cda4a44c91b3a0
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		compress/xz
COMPONENT_SUMMARY=	'XZ Utils - loss-less file compression application and library.'
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING.LGPLv2.1
COMPONENT_CLASSIFICATION= Applications/System Utilities

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-rpath

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

COMPONENT_TEST_DIR = $(@D)/tests

# The additional xz specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
        '-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
        '-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
        '-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
        '-e "/^XXX_CC_XXX$$/d" ' \
		'-e "/^make/d" ' \
		'-e "/^mv -f/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/xopen/xcu4
