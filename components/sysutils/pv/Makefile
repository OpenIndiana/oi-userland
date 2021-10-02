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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pv
COMPONENT_VERSION=	1.6.20
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_FMRI=		shell/pipe-viewer
COMPONENT_SUMMARY=	'Pipe Viewer'
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	pv.license
COMPONENT_PROJECT_URL=	https://www.ivarch.com/programs/pv.shtml
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:e831951eff0718fba9b1ef286128773b9d0e723e1fbfae88d5a3188814fdc603
COMPONENT_ARCHIVE_URL=	https://www.ivarch.com/programs/sources/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

PKG_PROTO_DIRS += $(BUILD_DIR_32)

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

ASLR_MODE = $(ASLR_ENABLE)
LD_Z_IGNORE =

COMPONENT_TEST_ENV +=  PATH="$(PATH.gnu)"

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/0/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
