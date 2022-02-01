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

BUILD_STYLE=justmake
BUILD_BITS=32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         bcc
COMPONENT_VERSION=      0.16.21
COMPONENT_PROJECT_URL=  https://github.com/lkundrak/dev86/
COMPONENT_SRC=          dev86-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:49c7ee9102d45c2eef072bfb8a49ba3821c9fe3ef31ccd3290f658b667b579a8
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		developer/bcc
COMPONENT_SUMMARY=	Bruce's C Compiler
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_LICENSE=	GPLv2

COMMON_TARGETS=no
TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Create the Makefile before we build
COMPONENT_PRE_BUILD_ACTION = \
  (cd $(@D) ; CC="$(CC)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" $(GMAKE) make.fil)
# build with the created Makefile (make.fil)
COMPONENT_BUILD_ARGS = -f make.fil
COMPONENT_BUILD_ARGS += PATH="$(@D)/bin:$(PATH)"
COMPONENT_BUILD_ARGS += MAKE="$(GMAKE)"
COMPONENT_BUILD_ARGS += VERSION="$(COMPONENT_VERSION)"
COMPONENT_BUILD_ARGS += TOPDIR="$(@D)"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_TARGETS = bcc86 as86 ld86 ar86


# common targets
install build:		$(BUILD_32)


# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
