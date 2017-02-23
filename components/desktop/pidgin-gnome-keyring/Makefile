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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
COMPILER= gcc
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pidgin-gnome-keyring
COMPONENT_VERSION=	2.0
COMPONENT_PROJECT_URL=	https://github.com/aebrahim/pidgin-gnome-keyring
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION).orig.tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:f75bc1a859226a5ad7cf3012925835a4d70b83dcac57a95d452194601b03191c
COMPONENT_ARCHIVE_URL=	http://archive.ubuntu.com/ubuntu/pool/universe/p/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pidgin
COMPONENT_ANITYA_ID=	13281

TPNO=			29496

# Pidgin is on the do-not-publish list (depends on S12-only changes in ON &
# Desktop), so no point publishing this without that.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

BUILD_STYLE= justmake
INSTALL_TARGET= build
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# VERSION is used by the build process.
COMPONENT_PRE_BUILD_ACTION += \
	echo $(COMPONENT_VERSION) > $(BUILD_DIR_64)/VERSION

COMPONENT_BUILD_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# The Makefile install target puts it in the 32-bit directory, so just get it
# from the build directory.
PKG_PROTO_DIRS += $(BUILD_DIR_64)

REQUIRED_PACKAGES += communication/im/pidgin
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += system/library
